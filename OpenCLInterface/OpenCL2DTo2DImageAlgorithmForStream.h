#pragma once

#include "OpenCLAlgorithmForStream.h"
#include "OpenCL2DTo2DImageAlgorithm.h"

class OpenCL2DTo2DImageAlgorithmForStream : public OpenCLAlgorithmForStream, public OpenCL2DTo2DImageAlgorithm
{
public:
  OpenCL2DTo2DImageAlgorithmForStream(void);
  ~OpenCL2DTo2DImageAlgorithmForStream(void);

#ifndef __unix__
  #pragma warning (disable :4250) //for disable warning in vs about inhertance via dominance, may not work in gcc
#endif
};

