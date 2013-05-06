#include "OpenCl3DImageAlgorithm.h"

#define ASSERT_OPENCL_ERR(ERR,MSG) if(ERR != CL_SUCCESS) \
{ \
  throw OpenCL3DImageException(MSG, ERR); \
}

OpenCL3DImageAlgorithm::OpenCL3DImageAlgorithm(void) : OpenCLImageCommon()
{
  width = height = depth = 0;
}

OpenCL3DImageAlgorithm::~OpenCL3DImageAlgorithm(void)
{
  clearAlgorithm();
}


void OpenCL3DImageAlgorithm::setDataSize(size_t w, size_t h, size_t d)
{
  width = w;
  height = h;
  depth = d;
}

void OpenCL3DImageAlgorithm::setIOArguments()
{
  cl_int err;

  input_image_memory = clCreateImage3D(context, CL_MEM_READ_ONLY, &input_image_format, width, height, depth, 0, 0, NULL, &err);
  ASSERT_OPENCL_ERR(err, "Error while creating image3D for input in OpenCL3DImageAlgorithm");

  err = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *) &input_image_memory);
  ASSERT_OPENCL_ERR(err, "Cant set kernel arg 0 of OpenCL3DImageAlgorithm");

  output_image_memory = clCreateImage3D(context, CL_MEM_READ_ONLY, &output_image_format, width, height, depth, 0, 0, NULL, &err);
  ASSERT_OPENCL_ERR(err, "Error while creating image3D for output in OpenCL3DImageAlgorithm");

  err = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *) &output_image_memory);
  ASSERT_OPENCL_ERR(err, "Cant set kernel arg 1 of OpenCL3DImageAlgorithm");
}

void OpenCL3DImageAlgorithm::setOtherArguments()
{
  //none
}