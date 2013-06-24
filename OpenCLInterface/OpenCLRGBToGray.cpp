#include "OpenCLRGBToGray.h"


OpenCLRGBToGray::OpenCLRGBToGray(void)
{
  input_image_format.image_channel_order = CL_RGBA;
  input_image_format.image_channel_data_type = CL_FLOAT;
  output_image_format.image_channel_order = CL_LUMINANCE;
  output_image_format.image_channel_data_type= CL_FLOAT;

  kernel_name = "rgb2gray";
  source_filename = "conversions.cl";
}


OpenCLRGBToGray::~OpenCLRGBToGray(void)
{
}


void OpenCLRGBToGray::copyDataToGPUStream()
{
}

void OpenCLRGBToGray::setKernelArgsForStream()
{
}