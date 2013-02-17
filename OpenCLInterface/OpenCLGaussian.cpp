#include "OpenCLGaussian.h"

#include <exception>

#define ASSERT_OPENCL_ERR(ERR,MSG) if(ERR != CL_SUCCESS) \
{ \
  throw OpenCLAlgorithmException(MSG, ERR); \
}

OpenCLGaussian::OpenCLGaussian(void)
{
}

OpenCLGaussian::~OpenCLGaussian(void)
{
}

void OpenCLGaussian::setParams(const OpenCLAlgorithmParams & params)
{
}

void OpenCLGaussian::prepare()
{
  command_queue = device.getCommandQueue();
  program = device.createAndBuildProgramFromFile("gaussian.cl"); //TODO: change path
  cl_int err;
  kernel = clCreateKernel(program, "gaussian", &err);
  ASSERT_OPENCL_ERR(err, "Cant create kernel");
}

void OpenCLGaussian::run(const unsigned char * data_input, size_t di_size, unsigned char * data_output, size_t do_size)
{
  cl_mem input, output, mask_mem;
  cl_int err;

  float mask[] = {(float) 0.1, (float) 0.1, (float) 0.1, (float) 0.1, (float) 0.1, (float) 0.1, (float) 0.1, (float) 0.1, (float) 0.1};

  input = clCreateBuffer(device.getContext(), CL_MEM_READ_ONLY, di_size, NULL, &err);
  ASSERT_OPENCL_ERR(err, "Error while creating buffer input");

  output = clCreateBuffer(device.getContext(), CL_MEM_WRITE_ONLY, do_size, NULL, &err);
  ASSERT_OPENCL_ERR(err, "Error while creating buffer output");

  mask_mem = clCreateBuffer(device.getContext(), CL_MEM_READ_ONLY, sizeof (mask), NULL, &err);
  ASSERT_OPENCL_ERR(err, "Error while creating buffer mask_mem");

  err = clEnqueueWriteBuffer(command_queue, input, CL_TRUE, 0, di_size, data_input, 0, NULL, NULL);
  ASSERT_OPENCL_ERR(err, "Error while enqueing wirte buffer for input");

  err = clEnqueueWriteBuffer(command_queue, mask_mem, CL_TRUE, 0, sizeof (mask), &mask, 0, NULL, NULL);
  ASSERT_OPENCL_ERR(err, "Error while enqueing wirte buffer for mask");

  err = clSetKernelArg(kernel, 0, sizeof (cl_mem), (void*) &mask_mem);
  ASSERT_OPENCL_ERR(err, "Cant set kernel arg 0");

  err = clSetKernelArg(kernel, 1, sizeof (cl_mem), (void*) &input);
  ASSERT_OPENCL_ERR(err, "Cant set kernel arg 1");

  err = clSetKernelArg(kernel, 2, sizeof (cl_mem), (void*) &output);
  ASSERT_OPENCL_ERR(err, "Cant set kernel arg 2")

  size_t global_work_size[] = {498, 498};

  enqueueNDRangeKernelWithTimeMeasurment(2, NULL, global_work_size, NULL, 0);

  //read data
  err = clEnqueueReadBuffer(command_queue, output, CL_TRUE, 0, do_size, data_output, 0, NULL, NULL);
  ASSERT_OPENCL_ERR(err, "Can't enqueue read buffer, output");

  clReleaseMemObject(input);
  clReleaseMemObject(output);
  clReleaseMemObject(mask_mem);
}

void OpenCLGaussian::releaseMem()
{
}

void OpenCLGaussian::setKernelArgs(size_t di_size, size_t do_size)
{
}

/******************** OpenCLGaussanImage ***********************/

OpenCLGaussianImage::OpenCLGaussianImage()
{
  input_format.image_channel_data_type = CL_FLOAT;
  input_format.image_channel_order = CL_LUMINANCE;

  output_format.image_channel_data_type = CL_FLOAT;
  output_format.image_channel_order = CL_LUMINANCE;

  kernel_name = "gaussian";
  source_file = "gaussian.cl";
}

OpenCLGaussianImage::~OpenCLGaussianImage()
{

}

void OpenCLGaussianImage::setParams(const OpenCLAlgorithmParams& params)
{
  try
  {
    setParams(dynamic_cast<OpenCLGaussinaParams&> (const_cast<OpenCLAlgorithmParams&>(params)));
  }
  catch(std::bad_cast ex)
  {
    throw OpenCLAlgorithmException("Parameters provided is not OpenCLGaussianParams");
  }
}

void OpenCLGaussianImage::setParams(const OpenCLGaussinaParams& params)
{

}

/*void OpenCLGaussianImage::prepareForStream(cl_command_queue cc, cl_context c)
{

}

void OpenCLGaussianImage::runStream(const size_t* global_work_size)
{

}
*/
void OpenCLGaussianImage::copyDataToGPUStream()
{

}

void OpenCLGaussianImage::setKernelArgsForStream()
{

}

void OpenCLGaussianImage::run(const unsigned char * data_input, size_t di_size, unsigned char * data_output, size_t do_size)
{

}

void OpenCLGaussianImage::releaseMem()
{

}

void OpenCLGaussianImage::setKernelArgs(size_t di_size, size_t do_size)
{

}
