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
  output_size = 0;
  output = nullptr;
}


OpenCLEdgeDetector::~OpenCLEdgeDetector(void)
{
  clearOutput();
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

  additional_output_image_memory = clCreateImage2D(context, CL_MEM_WRITE_ONLY, &output_image_format, width, height, 0, NULL, &err);
  ASSERT_OPENCL_ERR(err, "Can't create additional image for OpenCLEdgeDetector");

  err = setKernelArg(2, &additional_output_image_memory);
  ASSERT_OPENCL_ERR(err, "Can't set kernel arg 2 for OpenCLEdgeDetector");
}

void OpenCLEdgeDetector::obtainAdditionalOutput()
{
  clearOutput();
  output = new float[width * height];

  size_t origin[] = {0, 0, 0};
  size_t region[] = {width, height, 1};
  
  cl_int err = clEnqueueReadImage(command_queue, additional_output_image_memory, CL_TRUE, origin, region, 0, 0, output, 0, NULL, NULL);
  ASSERT_OPENCL_ERR(err, "Can't read aditional image for OpenCLEdgeDetector");
}


void OpenCLEdgeDetector::clearOutput()
{
  if (output)
  {
    delete [] output;
    output = nullptr;
  }
}

void * OpenCLEdgeDetector::additionalOutput() const
{
  return output;
}

