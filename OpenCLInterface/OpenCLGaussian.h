#pragma once

#include "OpenCLAlgorithm.h"

class OpenCLGaussian : public OpenCLAlgorithm
{
public:
  OpenCLGaussian(void);
  ~OpenCLGaussian(void);

  void setParams(const OpenCLAlgorithmParams & params);
  void prepare();
  void run(const unsigned char * data_input, size_t di_size, unsigned char * data_output, size_t do_size);
  void releaseMem();
  void setKernelArgs(size_t di_size, size_t do_size);
};

class OpenCLGaussinaParams : public OpenCLAlgorithmParams
{
  void * gaussian_mask;
  unsigned int mask_size;
  friend class OpenCLGaussianImage;
};

class OpenCLGaussianImage : public OpenCLImageAlgorithm
{
public:
  OpenCLGaussianImage(void);
  ~OpenCLGaussianImage(void);

  void setParams(const OpenCLAlgorithmParams & params);
  void setParams(const OpenCLGaussinaParams & params);
  
  //for stream
  void prepareForStream(cl_command_queue cc, cl_context c);
  void runStream(const size_t * global_work_size);
  void copyDataToGPUStream();
  void setKernelArgsForStream();

private:
  //memory for gaussian
  cl_mem gaussian;

  //params
  OpenCLGaussinaParams params;
};