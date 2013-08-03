#include "OpenCL3DTo2DImageAlgorithm.h"

#define ASSERT_OPENCL_ERR(ERR,MSG) if(ERR != CL_SUCCESS) \
{ \
  throw OpenCL3DTo2DImageException      (MSG, ERR); \
}


OpenCL3DTo2DImageAlgorithm::OpenCL3DTo2DImageAlgorithm(void) : OpenCLImageCommon()
{
  width = height = depth = 0;
}


OpenCL3DTo2DImageAlgorithm::~OpenCL3DTo2DImageAlgorithm(void)
{
}

void OpenCL3DTo2DImageAlgorithm::setIOArguments()
{
  cl_int err;

  input_image_memory = clCreateImage3D(context, CL_MEM_READ_ONLY, &input_image_format, width, height, depth, 0, 0, NULL, &err);
  ASSERT_OPENCL_ERR(err, "Error while creating image3D for input in OpenCL3DTo2DImageAlgorithm");

  err = setKernelArg(0, &input_image_memory);
  ASSERT_OPENCL_ERR(err, "Cant set kernel arg 0 of OpenCL3DImageAlgorithm");

  output_image_memory = clCreateImage2D(context, CL_MEM_WRITE_ONLY, &output_image_format, width, height, 0 , NULL, &err);
  ASSERT_OPENCL_ERR(err, "Error while creating image2D for output in OpenCL3DTo2DImageAlgorithm");

  err = setKernelArg(1, &output_image_memory);
  ASSERT_OPENCL_ERR(err, "Cant set kernel arg 1 of OpenCL3DImageAlgorithm");
}

void OpenCL3DTo2DImageAlgorithm::setOtherArguments()
{
  //none
}