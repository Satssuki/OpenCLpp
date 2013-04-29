#include "OpenCLLaplacian.h"


OpenCLLaplacian::OpenCLLaplacian(void)
{
}


OpenCLLaplacian::~OpenCLLaplacian(void)
{
}

void OpenCLLaplacian::setParams(const OpenCLAlgorithmParams& params)
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
  
}

void OpenCLLaplacian::setKernelArgsForStream()
{
  
}