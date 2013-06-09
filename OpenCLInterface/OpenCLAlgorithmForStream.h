#pragma once

#include "OpenCLImageCommon.h"

class OpenCLAlgorithmForStream : public virtual OpenCLImageCommon
{
public:
  OpenCLAlgorithmForStream(void);
  ~OpenCLAlgorithmForStream(void);

  friend class OpenCLAlgorithmsStream;

protected:
  virtual void prepareForStream(/*cl_command_queue cc, cl_context c)*/);
  virtual void runStream(const size_t * global_work_size);
  
  //pure virtual functions
  virtual void copyDataToGPUStream() = 0;
  virtual void setKernelArgsForStream() = 0;
};

