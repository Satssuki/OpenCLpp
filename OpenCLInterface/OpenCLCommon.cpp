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
