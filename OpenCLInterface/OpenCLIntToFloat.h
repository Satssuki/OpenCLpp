#pragma once

#include "OpenCLAlgorithm.h"

/**
 * Enum for selecting conversion.
 */
enum class OpenCLIntToFloatMode
{
  RGB_UINT_8,
  RGB_UINT_10,
  RGB_UINT_12,
  RGB_UINT_16,
  LUMINANCE_UINT_8,
  LUMINANCE_UINT_10,
  LUMINANCE_UINT_12,
  LUMINANCE_UINT_16
};

/**
 * Algorithm perfoming int to float conversion.
 */
class OpenCLIntToFloat : public OpenCLImageAlgorithm
{
public:
  OpenCLIntToFloat(OpenCLIntToFloatMode mode = OpenCLIntToFloatMode::LUMINANCE_UINT_8);
  ~OpenCLIntToFloat(void);
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

