#include "OpenCLFloatToInt.h"


OpenCLFloatToInt::OpenCLFloatToInt(OpenCLFloatToIntMode mode)
{
  switch (mode)
  {
    case OpenCLFloatToIntMode::LUMINANCE_UINT8:
    case OpenCLFloatToIntMode::RGB_UINT8:
      output_image_format.image_channel_data_type= CL_UNSIGNED_INT8;
      kernel_name = "floatToUInt8ThreeChannels";
      break;
    case OpenCLFloatToIntMode::LUMINANCE_UINT16:
    case OpenCLFloatToIntMode::RGB_UINT16:
      output_image_format.image_channel_data_type= CL_UNSIGNED_INT16;
      kernel_name = "floatToUInt16ThreeChannels";
      break;
    case OpenCLFloatToIntMode::LUMINANCE_UINT32:
    case OpenCLFloatToIntMode::RGB_UINT32:
      output_image_format.image_channel_data_type= CL_UNSIGNED_INT32;
      kernel_name = "floatToUInt32ThreeChannels";
      break;
    default:
      throw OpenCL2DTo2DImageException("Something went very wrong, because there is no other options");
  }

  switch (mode)
  {
  case OpenCLFloatToIntMode::LUMINANCE_UINT8:
  case OpenCLFloatToIntMode::LUMINANCE_UINT16:
  case OpenCLFloatToIntMode::LUMINANCE_UINT32:
    input_image_format.image_channel_order = CL_LUMINANCE;
    output_image_format.image_channel_order = CL_LUMINANCE;
    break;
  case OpenCLFloatToIntMode::RGB_UINT8:
  case OpenCLFloatToIntMode::RGB_UINT16:
  case OpenCLFloatToIntMode::RGB_UINT32:
    input_image_format.image_channel_order = CL_RGBA;
    output_image_format.image_channel_order = CL_RGBA;
    break;
  }

  //common  
  //input = output = NULL;
  input_image_format.image_channel_data_type = CL_FLOAT;

  source_filename = "conversions.cl";
  source = 
"__kernel void  floatToUInt8ThreeChannels(__read_only image2d_t input, __write_only image2d_t output) \n"
"{\n"
"  \n"
  "const int i = get_global_id(0); //row\n"
  "const int j = get_global_id(1); //column\n"
"\n"
  "float4 pixel = read_imagef(input, sampler, (int2)(i,j));\n"
"\n"
  "uint4 out = convert_uint4(pixel * 255.0);\n"
"  \n"
  "write_imageui(output, (int2)(i,j), out);\n"
"}\n"
"\n"
"__kernel void  floatToUInt16ThreeChannels(__read_only image2d_t input, __write_only image2d_t output) \n"
"{\n"
"  \n"
  "const int i = get_global_id(0); //row\n"
  "const int j = get_global_id(1); //column\n"
"\n"
  "float4 pixel = read_imagef(input, sampler, (int2)(i,j));\n"
"\n"
  "uint4 out = convert_uint4(pixel * 65535.0);\n"
"  \n"
  "write_imageui(output, (int2)(i,j), out);\n"
"}\n"
"\n"
"__kernel void  floatToUInt32ThreeChannels(__read_only image2d_t input, __write_only image2d_t output) \n"
"{\n"
"  \n"
  "const int i = get_global_id(0); //row\n"
  "const int j = get_global_id(1); //column\n"
"\n"
  "float4 pixel = read_imagef(input, sampler, (int2)(i,j));\n"
"\n"
  "uint4 out = convert_uint4(pixel * 4294967295.0);\n"
"  \n"
  "write_imageui(output, (int2)(i,j), out);\n"
"}\n"
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


OpenCLFloatToInt::~OpenCLFloatToInt(void)
{
}

void OpenCLFloatToInt::copyDataToGPUStream()
{
  //nothing to do now, because there is no other parameters
}

void OpenCLFloatToInt::setKernelArgsForStream()
{
  //nothing to do now, because there is no other parameters
}

void OpenCLFloatToInt::releaseMem ()
{
  //nothing to do now, because there is no other parameters
}

void OpenCLFloatToInt::setParams (const OpenCLAlgorithmParams& params)
{
  //nothing to do now, because there is no other parameters
}

void OpenCLFloatToInt::run (const unsigned char* data_input, size_t di_size, unsigned char* data_output, size_t do_size)
{
  //nothing to do now, because there is no other parameters
}

void OpenCLFloatToInt::setKernelArgs (size_t di_size, size_t do_size)
{
  //nothing to do now, because there is no other parameters 
}
