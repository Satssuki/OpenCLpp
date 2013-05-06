#pragma once
#include "OpenCLCommon.h"

class OpenCLImageCommon :
public OpenCLCommon
{
public:
  OpenCLImageCommon(void);
  ~OpenCLImageCommon(void);
  
protected:
  /**
   * Process image.
   * @param data_input Pointer to continious memory with input image. 
   * @param data_output  Pointer to continious memory to store 3D image. 
   */
  void processData(const void * data_input, void * data_output);
  
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

