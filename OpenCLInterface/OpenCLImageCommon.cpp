#include "OpenCLImageCommon.h"

#define ASSERT_OPENCL_ERR(ERR,MSG) if(ERR != CL_SUCCESS) \
{ \
  throw OpenCL3DImageException(MSG, ERR); \
}

OpenCLImageCommon::OpenCLImageCommon(void) : OpenCLCommon()
{
}


OpenCLImageCommon::~OpenCLImageCommon(void)
{
}

void OpenCLImageCommon::processData(const void* data_input, void* data_output)
{
  if (!prepared)
  {
    throw OpenCL3DImageException("Algorithm is not preapred");
  }

  cl_int err;
  time = 0;

  size_t origin[] = {0,0,0};
  size_t region[] = {width, height, depth};

  err = clEnqueueWriteImage(command_queue, input_image_memory, CL_FALSE, origin, region, 0, 0, data_input, 0, NULL, NULL);
  ASSERT_OPENCL_ERR(err, "Error while enqueue write image 3D");

  enqueueNDRangeKernelWithTimeMeasurment(3, NULL, region, NULL, 0);

  err = clEnqueueReadImage(command_queue, output_image_memory, CL_TRUE, origin, region, 0, 0, data_output, 0, NULL, NULL);
  ASSERT_OPENCL_ERR(err, "Error while enqueue read image 3D");

}