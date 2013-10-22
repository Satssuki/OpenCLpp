#include "OpenCLFindMaxin2DImage.h"


OpenCLFindMaxin2DImage::OpenCLFindMaxin2DImage(void)
{
  source_filename = "max2d.cl";
  kernel_name = "findLocalMax";
  source =
"const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP | CLK_FILTER_NEAREST;\n"
"\n"
"\n"
"__kernel void findLocalMax(__read_only image3d_t input, __write_only image2d_t output)\n"
"{\n"
"	int i = get_global_id(0); //column number\n"
  "int j = get_global_id(1); //row number\n"
  "int k = get_global_id(2); //depth number\n"
"	\n"
"	float4 sum = read_imagef(input, sampler, (int4)(i, j, k, 0));\n"
  "for (int ii = -1; ii < 2; ++ii)\n"
  "{\n"
"		for (int jj = -1; jj < 2; ++jj)\n"
    "{\n"
"			for (int kk = -1; kk < 2; ++kk)\n"
      "{\n"
"				if ((jj != 0 || kk != 0 || ii != 0) && read_imagef(input, sampler, (int4)(i + ii, j + jj, k + kk, 0)).x >= sum.x)\n"
        "{\n"
"					return;\n"
        "}\n"
      "}\n"
    "}\n"
  "}\n"
"	\n"
"	\n"
"	if (sum.x > 1e-5) \n"
  "{\n"
"		write_imageui(output, (int2)(i, j), k+1);\n"
  "}\n"
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
}