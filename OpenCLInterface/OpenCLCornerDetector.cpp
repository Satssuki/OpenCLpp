#include "OpenCLCornerDetector.h"

#define ASSERT_OPENCL_ERR(ERR,MSG) if(ERR != CL_SUCCESS) \
{ \
  throw OpenCLAlgorithmException(MSG, ERR); \
}

OpenCLCornerDetector::OpenCLCornerDetector(void)
{
  input_image_format.image_channel_data_type = CL_FLOAT;
  input_image_format.image_channel_order = CL_LUMINANCE;

  output_image_format.image_channel_data_type = CL_FLOAT;
  output_image_format.image_channel_order = CL_LUMINANCE;

  kernel_name = "corner_detector";
  source_filename = "detectors.cl";
}


OpenCLCornerDetector::~OpenCLCornerDetector(void)
{
}

void OpenCLCornerDetector::setParams(const OpenCLAlgorithmParams& params)
{ 
}

void OpenCLCornerDetector::releaseMem()
{
  //nothing to do here, image algorithm
}

void OpenCLCornerDetector::run(const unsigned char* data_input, size_t di_size, unsigned char* data_output, size_t do_size)
{
  //nothing to do here, image algorithm
}

void OpenCLCornerDetector::setKernelArgs(size_t di_size, size_t do_size)
{
  //nothing to do here, image algorithm
}

void OpenCLCornerDetector::copyDataToGPUStream()
{
}

void OpenCLCornerDetector::setKernelArgsForStream()
{
}
