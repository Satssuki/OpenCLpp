#pragma once

#include "OpenCL2DTo2DImageAlgorithm.h"

class OpenCLFindEdgesIn2DImageParams : public OpenCLAlgorithmParams
{
public:
  void setData(void * data)
  {
    Lvvv = data;
  }

private:
  friend class OpenCLFindEdgesIn2DImage;
  void * Lvvv;
};

class OpenCLFindEdgesIn2DImage :  public OpenCL2DTo2DImageAlgorithm
{
public:
  OpenCLFindEdgesIn2DImage(void);
  ~OpenCLFindEdgesIn2DImage(void);

  void setOtherArguments();

  void setParams(const OpenCLAlgorithmParams & params);
  void setParams(const OpenCLFindEdgesIn2DImageParams & params);

protected:
  void setKernelArguments();

private:
  void * Lvvv_image_data;
  cl_mem Lvvv_memory;
};

