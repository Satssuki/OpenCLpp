#include "OpenCLRidgeDetector.h"
#include "OpenCLException.h"

#define ASSERT_OPENCL_ERR(ERR,MSG) if(ERR != CL_SUCCESS) \
{ \
  throw OpenCLException(MSG, ERR); \
}

OpenCLRidgeDetector::OpenCLRidgeDetector(void)
{
  input_image_format.image_channel_data_type = CL_FLOAT;
  input_image_format.image_channel_order = CL_LUMINANCE;

  output_image_format.image_channel_data_type = CL_FLOAT;
  output_image_format.image_channel_order = CL_LUMINANCE;

  kernel_name = "ridge_detector";
  source_filename = "detectors.cl";

  source = 
"const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP_TO_EDGE | CLK_FILTER_NEAREST;\n"
"\n"
"__kernel void  ridge_detector(__read_only image2d_t input, __write_only image2d_t out_L1, __write_only\n" "image2d_t out_L2)\n"
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
  "float Lx =  0.5 * (ur + 2.0 * r + dr - ul - 2.0 * l - dl);\n"
  "float Ly =  0.5 * (dl + 2.0 * d + dr - ul - 2.0 * u - ur);\n"
  "float Lxx =  ul / 12.0 - u / 6.0 + ur / 12.0 +\n"
                "5.0 * l / 6.0 - 5.0 * c / 3.0 + 5.0 * r / 6.0 +\n"
        "dl / 12.0 - d / 6.0 + dr / 12.0;\n"
  "float Lxy =  ul / 4.0 - ur / 4.0 +\n"
        "-dl / 4.0 + dr / 4.0;//*/			\n"
  "float Lyy =  ul / 12.0 + 5.0 * u / 6.0 + ur / 12.0 -\n"
                "l / 6.0 - 5.0 * c / 3.0 - r / 6.0 +\n"
        "dl / 12.0 +  5.0 * d / 6.0 + dr / 12.0;\n"
"	\n"
"	float L1 = Lx * Ly * (Lxx - Lyy) - (Lx * Lx - Ly * Ly) * Lxy;\n"
  "if (fabs(L1) < 1e-5)\n"
  "{\n"
"		L1 = 0;\n"
  "}\n"
  "float L2 = (Ly * Ly - Lx * Lx) * (Lxx - Lyy) - 4 * Lx * Ly * Lxy;\n"
  "if (fabs(L2) < 1e-5)\n"
  "{\n"
"		L2 = 0;\n"
  "}\n"
"	\n"
"	write_imagef(out_L1, (int2)(i, j), L1);\n"
  "write_imagef(out_L2, (int2)(i, j), L2);\n"
"}\n";

  additional_output_image_memory = nullptr;
  output_size = 0;
  output = nullptr;
}


OpenCLRidgeDetector::~OpenCLRidgeDetector(void)
{
  clearOutput();
}

void OpenCLRidgeDetector::releaseMem()
{
  if (additional_output_image_memory)
  {
    clReleaseMemObject(additional_output_image_memory);
  }
  //nothing to do here, image algorithm
}

void OpenCLRidgeDetector::copyDataToGPUStream()
{
}

void OpenCLRidgeDetector::setKernelArgsForStream()
{
  cl_int err;

  additional_output_image_memory = clCreateImage2D(context, CL_MEM_WRITE_ONLY, &output_image_format, width, height, 0, NULL, &err);
  ASSERT_OPENCL_ERR(err, "Can't create additional image for OpenCLRidgeDetector");

  err = setKernelArg(2, &additional_output_image_memory);
  ASSERT_OPENCL_ERR(err, "Can't set kernel arg 2 for OpenCLRidgeDetector");
}

void OpenCLRidgeDetector::obtainAdditionalOutput()
{
  clearOutput();
  output = new float[width * height];

  size_t origin[] = {0, 0, 0};
  size_t region[] = {width, height, 1};
  
  cl_int err = clEnqueueReadImage(command_queue, additional_output_image_memory, CL_TRUE, origin, region, 0, 0, output, 0, NULL, NULL);
  ASSERT_OPENCL_ERR(err, "Can't read aditional image for OpenCLRidgeDetector");
}


void OpenCLRidgeDetector::clearOutput()
{
  if (output)
  {
    delete [] output;
    output = nullptr;
  }
}

void * OpenCLRidgeDetector::additionalOutput() const
{
  return output;
}

