#include "OpenCLFindEdgesIn2DImage.h"


OpenCLFindEdgesIn2DImage::OpenCLFindEdgesIn2DImage(void)
{
  source_filename = "max.cl";
  kernel_name = "edge_max";

  input_image_format.image_channel_data_type = CL_FLOAT;
  input_image_format.image_channel_order = CL_LUMINANCE;
    
  output_image_format.image_channel_data_type = CL_UNSIGNED_INT8;
  output_image_format.image_channel_order = CL_LUMINANCE;
}


OpenCLFindEdgesIn2DImage::~OpenCLFindEdgesIn2DImage(void)
{
}

void OpenCLFindEdgesIn2DImage::setOtherArguments()
{
  cl_int err;
  Lvvv_memory = clCreateImage2D(context, CL_MEM_READ_ONLY, &input_image_format, width, height, 0, NULL, &err);
  if (err)
  {
    throw OpenCL2DTo2DImageException("Error while create image 2D for Lvvv in edge find max", err);
  }

  //set zeros for output image
  char *zero_memory = new char[height * width];
  memset(zero_memory, 0, height * width);
  size_t origin[] = {0, 0, 0};
  size_t region[] = {width, height, 1};
  err = clEnqueueWriteImage(command_queue, output_image_memory, CL_FALSE, origin, region, 0, 0, (void*)zero_memory, 0, NULL, NULL);
  delete [] zero_memory;
  if (err)
  {
    throw OpenCL2DTo2DImageException("Error while enqueue write zero image", err);
  }
  
  err = setKernelArg(2, &Lvvv_memory);
  if (err)
  {
    throw OpenCL2DTo2DImageException("Can't set kernel arg Lvv for edge max", err);
  }
}

void OpenCLFindEdgesIn2DImage::setParams(const OpenCLAlgorithmParams & params)
{
  try
  {
    setParams(dynamic_cast<const OpenCLFindEdgesIn2DImageParams &>(params));
  }
  catch (std::bad_cast)
  {
    throw OpenCL2DTo2DImageException("Bad params for OpenCLFindEdgesIn2DImage", 0);
  }
}

void OpenCLFindEdgesIn2DImage::setParams(const OpenCLFindEdgesIn2DImageParams & params)
{
  Lvvv_image_data = params.Lvvv;
}

void OpenCLFindEdgesIn2DImage::setKernelArguments()
{
  size_t origin2[] = {0, 0, 0};
  size_t region2[] = {width, height, 1};

  cl_int err = clEnqueueWriteImage(command_queue, Lvvv_memory, CL_FALSE, origin2, region2, 0, 0, Lvvv_image_data, 0, NULL, NULL);
  if (err)
  {
    throw OpenCL2DTo2DImageException("Error while enqueue write Lvvv image in edge find max", err);
  }
}