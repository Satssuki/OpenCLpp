#include "OpenCLRGBToGray.h"


OpenCLRGBToGray::OpenCLRGBToGray(void)
{
  input_image_format.image_channel_order = CL_RGBA;
  input_image_format.image_channel_data_type = CL_FLOAT;
  output_image_format.image_channel_order = CL_LUMINANCE;
  output_image_format.image_channel_data_type= CL_FLOAT;

  kernel_name = "rgb2gray";
  //source_filename = "conversions.cl";
  source = 
"const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_NONE | CLK_FILTER_NEAREST;\n"
"\n"
"__kernel void rgb2gray(__read_only image2d_t input, __write_only image2d_t output) \n"
"{\n"
"  const int i = get_global_id(0); //row\n"
  "const int j = get_global_id(1); //column\n"
"\n"
  "float4 pixel = read_imagef(input, sampler, (int2)(i,j));\n"
"\n"
  "float out = 0.2126 * pixel.s1 + 0.7152 * pixel.s2 + 0.114 * pixel.s3;\n"
"  \n"
  "write_imagef(output, (int2)(i,j), out);\n"
"}\n";
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