#include "OpenCLEdgeDetector.h"
#include "OpenCLException.h"

#define ASSERT_OPENCL_ERR(ERR,MSG) if(ERR != CL_SUCCESS) \
{ \
  throw OpenCLException(MSG, ERR); \
}

OpenCLEdgeDetector::OpenCLEdgeDetector(void)
{
  input_image_format.image_channel_data_type = CL_FLOAT;
  input_image_format.image_channel_order = CL_LUMINANCE;

  output_image_format.image_channel_data_type = CL_FLOAT;
  output_image_format.image_channel_order = CL_LUMINANCE;

  kernel_name = "edge_detector";
  source_filename = "detectors.cl";

  additional_output_image_memory = nullptr;
}


OpenCLEdgeDetector::~OpenCLEdgeDetector(void)
{
}

void OpenCLEdgeDetector::releaseMem()
{
  if (additional_output_image_memory)
  {
    clReleaseMemObject(additional_output_image_memory);
  }
  //nothing to do here, image algorithm
}

void OpenCLEdgeDetector::copyDataToGPUStream()
{
}

void OpenCLEdgeDetector::setKernelArgsForStream()
{
  cl_int err;

  clCreateImage2D(context, CL_MEM_READ_ONLY, &output_image_format, width, height, 0, NULL, &err);
  ASSERT_OPENCL_ERR(err, "Can't create additional image for OpenCLEdgeDetector");

  err = setKernelArg(2, &additional_output_image_memory);
  ASSERT_OPENCL_ERR(err, "Can't set kernel arg 2 for OpenCLEdgeDetector");
}

void OpenCLEdgeDetector::obtainAdditionalOutput()
{
  size_t additional_output_image_size = width * height * sizeof(float);
  size_t origin[] = {0, 0, 0};
  size_t region[] = {height, width, 0};
  
  cl_int err = clEnqueueReadImage(command_queue, additional_output_image_memory, CL_TRUE, origin, region, 0, 0, &additional_output_image_size, 0, NULL, NULL);
  ASSERT_OPENCL_ERR(err, "Can't read aditional image for OpenCLEdgeDetector");
}
