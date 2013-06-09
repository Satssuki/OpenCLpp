#pragma once

#include "OpenCL2DTo2DImageAlgorithmForStream.h"

enum class OpenCLFloatToIntMode
{
  LUMINANCE_UINT8,
  LUMINANCE_UINT16,
  LUMINANCE_UINT32,
  RGB_UINT8,
  RGB_UINT16,
  RGB_UINT32 
};

/**
 * @brief Algorithm performs float to int conversion.
 * 
 * Possible output modes:
 * * OpenCLFloatToIntMode::UINT8 - 8 bit unsigned int
 * * OpenCLFloatToIntMode::UINT16 - 16 bit unsigned int
 * * OpenCLFloatToIntMode::UINT32 - 32 bit unsigned int
 */
class OpenCLFloatToInt : public OpenCL2DTo2DImageAlgorithmForStream
{
public:
  OpenCLFloatToInt(OpenCLFloatToIntMode mode = OpenCLFloatToIntMode::LUMINANCE_UINT8);
  ~OpenCLFloatToInt(void);
private:
//from OpenCLImageAlgorithm
  void copyDataToGPUStream();
  void setKernelArgsForStream();

  //from OpenCLAlgorithm
  void releaseMem();
  void setParams(const OpenCLAlgorithmParams & params);
  void run(const unsigned char * data_input, size_t di_size, unsigned char * data_output, size_t do_size);
  void setKernelArgs(size_t di_size, size_t do_size);
};


