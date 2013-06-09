#include "OpenCLAlgorithmForStream.h"


OpenCLAlgorithmForStream::OpenCLAlgorithmForStream(void)
{
}


OpenCLAlgorithmForStream::~OpenCLAlgorithmForStream(void)
{
}

void OpenCLAlgorithmForStream::prepareForStream(/*cl_command_queue cc, cl_context c*/)
{
  std::string error_string;
  /*
  command_queue = cc;
  context = c;*/

  createKernel();
  setKernelArgsForStream();
}

void OpenCLAlgorithmForStream::runStream(const size_t * global_work_size)
{
  copyDataToGPUStream();
  enqueueNDRangeKernelWithTimeMeasurment(2, NULL, global_work_size, NULL, 0);
}
