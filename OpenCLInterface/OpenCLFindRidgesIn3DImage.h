#pragma once

#include "OpenCL3DTo2DImageAlgorithm.h"

class OpenCLFindRidgesIn3DImageParams : public OpenCLAlgorithmParams
{
public:
  void setData(void * data)
  {
    L2 = data;
  }

private:
  friend class OpenCLFindRidgesIn3DImage;
  void * L2;
};

class OpenCLFindRidgesIn3DImage :  public OpenCL3DTo2DImageAlgorithm
{
public:
  OpenCLFindRidgesIn3DImage(void);
  ~OpenCLFindRidgesIn3DImage(void);

  void setOtherArguments();

  void setParams(const OpenCLAlgorithmParams & params);
  void setParams(const OpenCLFindRidgesIn3DImageParams & params);

protected:
  void setKernelArguments();

private:
  void * L2_image_data;
  cl_mem L2_memory;
};

