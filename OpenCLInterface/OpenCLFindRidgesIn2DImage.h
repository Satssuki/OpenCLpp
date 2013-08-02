#pragma once

#include "OpenCL2DTo2DImageAlgorithm.h"

class OpenCLFindRidgesIn2DImageParams : public OpenCLAlgorithmParams
{
public:
  void setData(void * data)
  {
    L2 = data;
  }

private:
  friend class OpenCLFindRidgesIn2DImage;
  void * L2;
};

class OpenCLFindRidgesIn2DImage :  public OpenCL2DTo2DImageAlgorithm
{
public:
  OpenCLFindRidgesIn2DImage(void);
  ~OpenCLFindRidgesIn2DImage(void);

  void setOtherArguments();

  void setParams(const OpenCLAlgorithmParams & params);
  void setParams(const OpenCLFindRidgesIn2DImageParams & params);

protected:
  void setKernelArguments();

private:
  void * L2_image_data;
  cl_mem L2_memory;
};

