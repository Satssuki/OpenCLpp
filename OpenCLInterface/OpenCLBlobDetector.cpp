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
  source = 
"const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP_TO_EDGE | CLK_FILTER_NEAREST;\n"
"\n"
"__kernel void  blob_detector(__read_only image2d_t input, __write_only image2d_t output)\n"
"{\n"
"	int i = get_global_id(0); //column number\n"
  "int j = get_global_id(1); //row number\n"
"\n"
  "float ul = read_imagef(input, sampler, (int2)(i - 1, j - 1)).x;\n"
  "float u = read_imagef(input, sampler, (int2)(i, j - 1)).x;\n"
  "float ur = read_imagef(input, sampler, (int2)(i + 1, j - 1)).x;\n"
  "float l = read_imagef(input, sampler, (int2)(i - 1, j)).x;\n"
  "float c = read_imagef(input, sampler, (int2)(i, j)).x;\n"
  "float r = read_imagef(input, sampler, (int2)(i + 1, j)).x;\n"
  "float dl = read_imagef(input, sampler, (int2)(i - 1, j + 1)).x;\n"
  "float d = read_imagef(input, sampler, (int2)(i, j + 1)).x;\n"
  "float dr = read_imagef(input, sampler, (int2)(i + 1, j + 1)).x;\n"
"\n"
  "float Lxx =  ul / 12.0 - u / 6.0 + ur / 12.0 +\n"
                "5.0 * l / 6.0 - 5.0 * c / 3.0 + 5.0 * r / 6.0 +\n"
        "dl / 12.0 - d / 6.0 + dr / 12.0;//*/\n"
  "float Lyy =  ul / 12.0 + 5.0 * u / 6.0 + ur / 12.0 -\n"
                "l / 6.0 - 5.0 * c / 3.0 - r / 6.0 +\n"
        "dl / 12.0 +  5.0 * d / 6.0 + dr / 12.0;\n"
"	\n"
"	write_imagef(output, (int2)(i, j), fabs(Lxx + Lyy));\n"
"	\n"
"}\n"
"\n";
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
