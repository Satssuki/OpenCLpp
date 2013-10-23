#include "OpenCLFindMaxin2DImage.h"


OpenCLFindMaxin2DImage::OpenCLFindMaxin2DImage(void)
{
  //source_filename = "max2d.cl";
  kernel_name = "findLocalMax";
  source =
"const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP | CLK_FILTER_NEAREST;\n"
"\n"
"__kernel void findLocalMax(__read_only image2d_t input, __write_only image2d_t output)\n"
"{\n"
"	int i = get_global_id(0); //column number\n"
  "int j = get_global_id(1); //row number\n"
"	\n"
"	float sum = read_imagef(input, sampler, (int2)(i, j)).x;\n"
  "for (int ii = -1; ii < 2; ++ii)\n"
  "{\n"
"		for (int jj = -1; jj < 2; ++jj)\n"
    "{\n"
"			if (read_imagef(input, sampler, (int2)(i + ii, j + jj)).x > sum)\n"
      "{\n"
"				return;\n"
      "}\n"
    "}\n"
  "}\n"
"		\n"
  "if (sum > 1e-5) \n"
  "{\n"
"		write_imageui(output, (int2)(i, j), 255);\n"
  "}\n"
"	else\n"
"	{\n"
"		write_imageui(output, (int2)(i, j), 0);\n"
"	}\n"
"}\n"
"\n";

  input_image_format.image_channel_data_type = CL_FLOAT;
  input_image_format.image_channel_order = CL_LUMINANCE;
    
  output_image_format.image_channel_data_type = CL_UNSIGNED_INT8;
  output_image_format.image_channel_order = CL_LUMINANCE;
}


OpenCLFindMaxin2DImage::~OpenCLFindMaxin2DImage(void)
{
}

void OpenCLFindMaxin2DImage::setOtherArguments()
{
#if 0
  //set zeros for output image
  char *zero_memory = new char[height * width];
  memset(zero_memory, 0, height * width);
  size_t origin[] = {0, 0, 0};
  size_t region[] = {width, height, 1};
  cl_int err = clEnqueueWriteImage(command_queue, output_image_memory, CL_FALSE, origin, region, 0, 0, (void*)zero_memory, 0, NULL, NULL);
  delete [] zero_memory;
  if (err)
  {
    throw OpenCL2DTo2DImageException("Error while enqueue write zero image", err);
  }  
#endif // 0

}