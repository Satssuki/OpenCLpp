#pragma once
#include "OpenCLAlgorithm.h"

/** Algoritm performs Laplacian on image.
 * 
 */
class OpenCLLaplacian : public OpenCLImageAlgorithm
{
public:
  OpenCLLaplacian(void);
  ~OpenCLLaplacian(void);

  //from OpenCLAlgorithm
  virtual void setParams(const OpenCLAlgorithmParams & params) = 0;
  virtual void run(const unsigned char * data_input, size_t di_size, unsigned char * data_output, size_t do_size) = 0;
  virtual void setKernelArgs(size_t di_size, size_t do_size) = 0;

protected:
  //from OpenCLImageAlgorithm
  virtual void copyDataToGPUStream() = 0;
  virtual void setKernelArgsForStream() = 0;

private:
  //gaussian kernel
  void * laplacian;
  unsigned int size;
  unsigned int size_to_pass;

  cl_image_format laplacian_format;
  cl_mem laplacian_memory;
  cl_mem size_memory;
};

