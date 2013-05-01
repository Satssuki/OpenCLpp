#include "OpenCLCommon.h"

#define ASSERT_OPENCL_ERR(ERR,MSG) if(ERR != CL_SUCCESS) \
{ \
  throw OpenCLException(MSG, ERR); \
}

OpenCLCommon::OpenCLCommon(void)
{
}


OpenCLCommon::~OpenCLCommon(void)
{
}

void OpenCLCommon::setDevice(const OpenCLDevice& dev)
{
  if (dev.isValid())
  {
    device = dev;
    setDevice();
    return;
  }
  throw OpenCLException("Invalid Device", 0);
}

void OpenCLCommon::setDevice()
{
  command_queue = device.getCommandQueue();
  context = device.getContext();
}

void OpenCLCommon::createKernel()
{
  if (!source_filename.empty())
  {
    program = device.createAndBuildProgramFromFile(source_filename);
  }
  else if (!source.empty())
  {
    program = device.createAndBuildProgramFromSource(source);
  }
  else
  {
    std::string error_string = "Not written kernel: " + kernel_name;
    throw OpenCLException(kernel_name, 0);
  }
 
  cl_int err;
  kernel = clCreateKernel(program, kernel_name.c_str(), &err);
  std::string error_string = "Cant create kernel: " + kernel_name;
  ASSERT_OPENCL_ERR(err, error_string);
}

void OpenCLCommon::enqueueNDRangeKernelWithTimeMeasurment(cl_uint work_dim, size_t * global_work_offset, const size_t *global_work_size, const size_t *local_work_size, cl_uint num_events_in_wait_list)
{
  cl_event event;
  //start kernel
  clFinish(command_queue);
  int err = clEnqueueNDRangeKernel(command_queue, kernel, work_dim, global_work_offset, global_work_size, local_work_size, num_events_in_wait_list, NULL, &event);
  if (err)
  {
    throw OpenCLException("Cant enqueue nd range kernel", err);
  }
  clWaitForEvents(1, &event);

  //calculate time
  cl_ulong start, end;
  clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(start), &start, NULL);
  clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(end), &end, NULL);
  time = (end - start) / 1000000.0;
  clReleaseEvent(event);
}