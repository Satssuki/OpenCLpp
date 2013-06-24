#pragma once

#include "OpenCL2DTo2DImageAlgorithmForStream.h"

class OpenCLRGBToGray : public OpenCL2DTo2DImageAlgorithmForStream
{
public:
  OpenCLRGBToGray(void);
  ~OpenCLRGBToGray(void);

protected:
  void copyDataToGPUStream();
  void setKernelArgsForStream();
};

