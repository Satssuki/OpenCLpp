#include "OpenCLFindMaxin3DImage.h"


OpenCLFindMaxin3DImage::OpenCLFindMaxin3DImage(void)
{
  source_filename = "max.cl";
  kernel_name = "findLocalMax";

  input_image_format.image_channel_data_type = CL_UNSIGNED_INT8;
  input_image_format.image_channel_order = CL_LUMINANCE;
    
  output_image_format.image_channel_data_type = CL_UNSIGNED_INT8;
  output_image_format.image_channel_order = CL_LUMINANCE;
}


OpenCLFindMaxin3DImage::~OpenCLFindMaxin3DImage(void)
{
}
