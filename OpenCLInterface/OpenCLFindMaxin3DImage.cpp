#include "OpenCLFindMaxin3DImage.h"


OpenCLFindMaxin3DImage::OpenCLFindMaxin3DImage(void)
{
  source_filename = "max.cl";
  kernel_name = "findLocalMax";

  input_image_format.image_channel_data_type = CL_FLOAT;
  input_image_format.image_channel_order = CL_LUMINANCE;
    
  output_image_format.image_channel_data_type = CL_UNSIGNED_INT8;
  output_image_format.image_channel_order = CL_LUMINANCE;
}


OpenCLFindMaxin3DImage::~OpenCLFindMaxin3DImage(void)
{
}

void OpenCLFindMaxin3DImage::setOtherArguments()
{
  char *zero_memory = new char[height * width];
  memset(zero_memory, 0, height * width);
  size_t origin[] = {0, 0, 0};
  size_t region[] = {width, height, 1};
  cl_int err = clEnqueueWriteImage(command_queue, output_image_memory, CL_FALSE, origin, region, 0, 0, (void*)zero_memory, 0, NULL, NULL);
  delete [] zero_memory;
  if (err)
  {
    throw OpenCL3DTo2DImageException("Error while enqueue write zero image", err);
  }
}