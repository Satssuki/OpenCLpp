#pragma once
#include "OpenCLCommon.h"

class OpenCLImageCommon :
public OpenCLCommon
{
public:
  OpenCLImageCommon(void);
  ~OpenCLImageCommon(void);
  
  /**
   * Process image.
   * @param data_input Pointer to continious memory with input image. 
   * @param data_output  Pointer to continious memory to store image. 
   */
  void processData(const void * data_input, void * data_output);

   /**
   * Set 3D and 2D image size. For 2D images only width and height is relevant and depth is not need to be provided.
   * @param w Image width.
   * @param h Image height.
   * @param d Image depth.
   */
  virtual void setDataSize(size_t w, size_t h, size_t d = 0);
  
protected:

  virtual void setKernelArguments();
  
  /**
   * Clears algorithm.
   */
  void clearAlgorithm();
  
  size_t height, width, depth;
  
  cl_mem input_image_memory;
  cl_mem output_image_memory;

  cl_image_format input_image_format;
  cl_image_format output_image_format;
};

