#pragma once

#include "OpenCL2DTo2DImageAlgorithm.h"

class OpenCLFindMaxin2DImage :  public OpenCL2DTo2DImageAlgorithm
{
public:
  OpenCLFindMaxin2DImage(void);
  ~OpenCLFindMaxin2DImage(void);

  void setOtherArguments();
};

