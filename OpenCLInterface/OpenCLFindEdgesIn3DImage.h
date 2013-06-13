#pragma once

#include "OpenCL3DTo2DImageAlgorithm.h"

class OpenCLFindEdgesIn3DImageParams : public OpenCLAlgorithmParams
{
public:
  void setData(void * data)
  {
    Lvvv = data;
  }

private:
  friend class OpenCLFindEdgesIn3DImage;
  void * Lvvv;
};

class OpenCLFindEdgesIn3DImage :  public OpenCL3DTo2DImageAlgorithm
{
public:
  OpenCLFindEdgesIn3DImage(void);
  ~OpenCLFindEdgesIn3DImage(void);

  void setOtherArguments();

  void setParams(const OpenCLAlgorithmParams & params);
  void setParams(const OpenCLFindEdgesIn3DImageParams & params);

protected:
  void setKernelArguments();

private:
  void * Lvvv_image_data;
  cl_mem Lvvv_memory;
};

