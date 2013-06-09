#include "OpenCLBlobDetector.h"

#define ASSERT_OPENCL_ERR(ERR,MSG) if(ERR != CL_SUCCESS) \
{ \
  throw OpenCLAlgorithmException(MSG, ERR); \
}

OpenCLBlobDetector::OpenCLBlobDetector(void)
{
  input_image_format.image_channel_data_type = CL_FLOAT;
  input_image_format.image_channel_order = CL_LUMINANCE;

  output_image_format.image_channel_data_type = CL_FLOAT;
  output_image_format.image_channel_order = CL_LUMINANCE;

  kernel_name = "blob_detector";
  source_filename = "detectors.cl";
}


OpenCLBlobDetector::~OpenCLBlobDetector(void)
{
}

void OpenCLBlobDetector::setParams(const OpenCLAlgorithmParams& params)
{ 
}

void OpenCLBlobDetector::releaseMem()
{
  //nothing to do here, image algorithm
}

void OpenCLBlobDetector::run(const unsigned char* data_input, size_t di_size, unsigned char* data_output, size_t do_size)
{
  //nothing to do here, image algorithm
}

void OpenCLBlobDetector::setKernelArgs(size_t di_size, size_t do_size)
{
  //nothing to do here, image algorithm
}

void OpenCLBlobDetector::copyDataToGPUStream()
{
}

void OpenCLBlobDetector::setKernelArgsForStream()
{
}
