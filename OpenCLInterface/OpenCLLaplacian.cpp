#include "OpenCLLaplacian.h"

#define ASSERT_OPENCL_ERR(ERR,MSG) if(ERR != CL_SUCCESS) \
{ \
  throw OpenCL2DTo2DImageException(MSG, ERR); \
}

OpenCLLaplacian::OpenCLLaplacian(void)
{
  input_image_format.image_channel_data_type = CL_FLOAT;
  input_image_format.image_channel_order = CL_LUMINANCE;

  output_image_format.image_channel_data_type = CL_FLOAT;
  output_image_format.image_channel_order = CL_LUMINANCE;

  laplacian_format.image_channel_data_type = CL_FLOAT;
  laplacian_format.image_channel_order = CL_LUMINANCE;  

  kernel_name = "laplacian";
  source_filename = "convolution.cl";
  source = 
"const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP_TO_EDGE | CLK_FILTER_NEAREST;\n"
"\n"
"__kernel void  laplacian(__read_only image2d_t input, __write_only image2d_t output, __read_only\n" "image2d_t gaussian, __global __read_only uint * size, __global __read_only float * sigma) \n"
"{\n"
"  int width_output = get_global_size(0); \n"
  "int width = get_global_size(0); \n"
"\n"
  "int i = get_global_id(0); //column number\n"
  "int j = get_global_id(1); //row number\n"
  "float sum = 0.0;\n"
"  \n"
  "int sizeq = size[0];\n"
  "for (int i_gaussian = -sizeq; i_gaussian <= sizeq; ++i_gaussian)\n"
  "{\n"
"	for (int j_gaussian = -sizeq; j_gaussian <= sizeq; ++j_gaussian)\n"
  "{\n"
    "sum += (read_imagef(input, sampler, (int2)(i + i_gaussian, j + j_gaussian)).x *\n" "read_imagef(gaussian, sampler, (int2)(i_gaussian + sizeq, j_gaussian + sizeq))).x;\n"
  "}\n"
  "}\n"
"  \n"
  "sum = fabs(sum * sigma[0]);\n"
"  \n"
  "write_imagef(output, (int2)(i,j), sum);\n"
"  \n"
"}\n"
"\n";

  size = 3;
  size_to_pass = 1;
  
  float * tmp = new float[9];
  for (int i=0; i<9; ++i)
  {
    tmp[i] = 1.0f;
  }
  tmp[4] = -8.0f;

  laplacian = reinterpret_cast<void*>(tmp);

  laplacian_memory = nullptr;
  size_memory = nullptr;
  sigma_memory = nullptr;
}


OpenCLLaplacian::~OpenCLLaplacian(void)
{
  if (laplacian_memory != nullptr)
  {
    ASSERT_OPENCL_ERR(clReleaseMemObject(laplacian_memory), "Error during releasing laplacian memory");
  }
  if (size_memory != nullptr)
  {
    ASSERT_OPENCL_ERR(clReleaseMemObject(size_memory), "Error during releasing laplacian memory");
  }
  if (sigma_memory != nullptr)
  {
    ASSERT_OPENCL_ERR(clReleaseMemObject(sigma_memory), "Error during releasing laplacian memory");
  }
  //TODO: Remove laplacian
}

void OpenCLLaplacian::setParams(const OpenCLAlgorithmParams& params)
{ 
  try
  {
    setParams(dynamic_cast<const OpenCLLaplacianParams&> (params));
  }
  catch(std::bad_cast ex)
  {
    throw OpenCL2DTo2DImageException("Parameters provided is not OpenCLGaussianParams");
  }
}

void OpenCLLaplacian::setParams(const OpenCLLaplacianParams& params)
{
  sigma = params.sigma;
}

void OpenCLLaplacian::releaseMem()
{
  //nothing to do here, image algorithm
}

void OpenCLLaplacian::run(const unsigned char* data_input, size_t di_size, unsigned char* data_output, size_t do_size)
{
  //nothing to do here, image algorithm
}

void OpenCLLaplacian::setKernelArgs(size_t di_size, size_t do_size)
{
  //nothing to do here, image algorithm
}

void OpenCLLaplacian::copyDataToGPUStream()
{
  cl_int err;
  size_t origin[] = {0,0,0};
  size_t region[] = {size, size, 1};

  err = clEnqueueWriteBuffer(command_queue, size_memory, CL_FALSE, 0, sizeof(size_to_pass), &size_to_pass, 0, NULL, NULL);
  ASSERT_OPENCL_ERR(err, "Error while enqueing wirte buffer for size");

  err = clEnqueueWriteImage(command_queue, laplacian_memory, CL_FALSE, origin, region, 0, 0, laplacian, 0, NULL, NULL);
  ASSERT_OPENCL_ERR(err, "Error while enqueue write laplacian image");
  
  err = clEnqueueWriteBuffer(command_queue, sigma_memory, CL_FALSE, 0, sizeof(sigma), &sigma, 0, NULL, NULL);
  ASSERT_OPENCL_ERR(err, "Error while enqueing wirte buffer for sigma");
}

void OpenCLLaplacian::setKernelArgsForStream()
{
  cl_int err;

  laplacian_memory = clCreateImage2D(context, CL_MEM_READ_ONLY, &laplacian_format, size, size, 0, NULL, &err);
  ASSERT_OPENCL_ERR(err, "Error while creating laplacian image");
  
  err = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&laplacian_memory);
  ASSERT_OPENCL_ERR(err, "Error while setting as arg: laplacian image");

  size_memory = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(size_to_pass), NULL, &err);
  ASSERT_OPENCL_ERR(err, "Error while creating laplacian size");
  
  err = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)&size_memory);
  ASSERT_OPENCL_ERR(err, "Error while setting as arg: laplacian size");
  
  sigma_memory = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(sigma), NULL, &err);
  ASSERT_OPENCL_ERR(err, "Error while creating laplacian sigma");
  
  err = clSetKernelArg(kernel, 4, sizeof(cl_mem), (void*)&sigma_memory);
  ASSERT_OPENCL_ERR(err, "Error while setting as arg: laplacian sigma");
}

/*** OpenCLLaplacianParams ***/

void OpenCLLaplacianParams::setSigma(float sigma)
{
  this->sigma = sigma;
}