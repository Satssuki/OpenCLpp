#include "OpenCL2DTo2DImageAlgorithm.h"


#define ASSERT_OPENCL_ERR(ERR,MSG) if(ERR != CL_SUCCESS) \
{ \
  throw OpenCL2DTo2DImageException      (MSG, ERR); \
}


OpenCL2DTo2DImageAlgorithm::OpenCL2DTo2DImageAlgorithm(void) : OpenCLImageCommon()
{
  width = height = 0;
  depth = 1;
}


OpenCL2DTo2DImageAlgorithm::~OpenCL2DTo2DImageAlgorithm(void)
{
}

void OpenCL2DTo2DImageAlgorithm::setDataSize(size_t w, size_t h, size_t d)
{
  width = w;
  height = h;
}

void OpenCL2DTo2DImageAlgorithm::setIOArguments()
{
  cl_int err;

  input_image_memory = clCreateImage2D(context, CL_MEM_READ_ONLY, &input_image_format, width, height, 0, NULL, &err);
  ASSERT_OPENCL_ERR(err, "Error while creating image2D for input in OpenCL2DTo2DImageAlgorithm");

  err = setKernelArg(0, &input_image_memory);
  ASSERT_OPENCL_ERR(err, "Cant set kernel arg 0 of OpenCL2DTo2DImageAlgorithm");

  output_image_memory = clCreateImage2D(context, CL_MEM_READ_WRITE, &output_image_format, width, height, 0 , NULL, &err);
  ASSERT_OPENCL_ERR(err, "Error while creating image2D for output in OpenCL2DTo2DImageAlgorithm");

  err = setKernelArg(1, &output_image_memory);
  ASSERT_OPENCL_ERR(err, "Cant set kernel arg 1 of OpenCL2DTo2DImageAlgorithm");
}

void OpenCL2DTo2DImageAlgorithm::setOtherArguments()
{
  //none
}
