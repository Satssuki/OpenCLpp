#include "OpenCLIntToFloat.h"


OpenCLIntToFloat::OpenCLIntToFloat(OpenCLIntToFloatMode mode)
{
  //select resolution
  switch (mode)
  {
  case OpenCLIntToFloatMode::LUMINANCE_UINT_8:
  case OpenCLIntToFloatMode::RGB_UINT_8:
    input_format.image_channel_data_type = CL_UNSIGNED_INT8;
    kernel_name = "intToFloat8bit";
    break;
  case OpenCLIntToFloatMode::LUMINANCE_UINT_10:
  case OpenCLIntToFloatMode::RGB_UINT_10:
    input_format.image_channel_data_type = CL_UNSIGNED_INT16;
    kernel_name = "intToFloat10bit";
    break;
  case OpenCLIntToFloatMode::LUMINANCE_UINT_12:
  case OpenCLIntToFloatMode::RGB_UINT_12:
    input_format.image_channel_data_type = CL_UNSIGNED_INT16;
    kernel_name = "intToFloat12bit";
    break;
  case OpenCLIntToFloatMode::LUMINANCE_UINT_16:
  case OpenCLIntToFloatMode::RGB_UINT_16:
    input_format.image_channel_data_type = CL_UNSIGNED_INT16;
    kernel_name = "intToFloat16bit";
    break;
  default:
    throw OpenCLAlgorithmException("Something went very wrong, because there is no other options for OpenCLIntToFloatMode");
  }

  //select data type
  switch (mode)
  {
  case OpenCLIntToFloatMode::LUMINANCE_UINT_8:
  case OpenCLIntToFloatMode::LUMINANCE_UINT_10:
  case OpenCLIntToFloatMode::LUMINANCE_UINT_12:
  case OpenCLIntToFloatMode::LUMINANCE_UINT_16:
    input_format.image_channel_order = CL_LUMINANCE;
    output_format.image_channel_order = CL_LUMINANCE;
    break;
  case OpenCLIntToFloatMode::RGB_UINT_8:
  case OpenCLIntToFloatMode::RGB_UINT_10:
  case OpenCLIntToFloatMode::RGB_UINT_12:
  case OpenCLIntToFloatMode::RGB_UINT_16:
    input_format.image_channel_order = CL_RGBA;
    output_format.image_channel_order = CL_RGBA;
    break;
  default:
    throw OpenCLAlgorithmException("Something went very wrong, because there is no other options for OpenCLIntToFloatMode and it was checked");
  }

  //common
  input = output = NULL;
  output_format.image_channel_data_type= CL_FLOAT;

  //source
  source_file = "conversions.cl";
  source = "";
  /*
  source = "const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_NONE | CLK_FILTER_NEAREST;\n"
"\n"
"__kernel void  intToFloat8bit(__read_only image2d_t input, __write_only image2d_t output) \n"
"{\n"
"  \n"
  "const int i = get_global_id(0); //row\n"
  "const int j = get_global_id(1); //column\n"
"\n"
"float4 pixel = convert_float4(read_imageui(input, sampler, (int2)(i,j)));\n"
"\n"
  "float4 out;\n"
  "out = pixel / 255.0;\n"
"  \n"
  "write_imagef(output, (int2)(i,j), out);\n"
"}\n"
"\n"
"__kernel void  intToFloat10bit(__read_only image2d_t input, __write_only image2d_t output) \n"
"{\n"
"  \n"
  "const int i = get_global_id(0); //row\n"
  "const int j = get_global_id(1); //column\n"
"\n"
  "uint4 pixel = read_imageui(input, sampler, (int2)(i,j));\n"
"\n"
  "float4 out;\n"
  "out = pixel / 1023.0;\n"
"  \n"
  "write_imagef(output, (int2)(i,j), out);\n"
"}\n"
"\n"
"__kernel void  intToFloat12bit(__read_only image2d_t input, __write_only image2d_t output) \n"
"{\n"
"  \n"
  "const int i = get_global_id(0); //row\n"
  "const int j = get_global_id(1); //column\n"
"\n"
  "uint4 pixel = read_imageui(input, sampler, (int2)(i,j));\n"
"\n"
  "float4 out;\n"
  "out = pixel / 4095.0;\n"
"  \n"
  "write_imagef(output, (int2)(i,j), out);\n"
"}\n"
"\n"
"__kernel void  intToFloat16bit(__read_only image2d_t input, __write_only image2d_t output) \n"
"{\n"
"  \n"
  "const int i = get_global_id(0); //row\n"
  "const int j = get_global_id(1); //column\n"
"\n"
  "uint4 pixel = read_imageui(input, sampler, (int2)(i,j));\n"
"\n"
  "float4 out;\n"
  "out = pixel / 65535.0;\n"
"  \n"
  "write_imagef(output, (int2)(i,j), out);\n"
"}\n";*/
}


OpenCLIntToFloat::~OpenCLIntToFloat(void)
{
}

void OpenCLIntToFloat::copyDataToGPUStream()
{
  //nothing to do now, before there is no other parameters
}

void OpenCLIntToFloat::setKernelArgsForStream()
{
  //nothing to do now, before there is no other parameters
}

void OpenCLIntToFloat::releaseMem ()
{
  //nothing to do now, before there is no other parameters
}

void OpenCLIntToFloat::setParams (const OpenCLAlgorithmParams& params)
{
  //nothing to do now, before there is no other parameters
}

void OpenCLIntToFloat::run (const unsigned char* data_input, size_t di_size, unsigned char* data_output, size_t do_size)
{
  //nothing to do now, before there is no other parameters
}

void OpenCLIntToFloat::setKernelArgs (size_t di_size, size_t do_size)
{
  //nothing to do now, before there is no other parameters 
}
