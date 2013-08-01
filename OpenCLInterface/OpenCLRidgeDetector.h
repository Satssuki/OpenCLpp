#pragma once
#include "OpenCL2DTo2DImageAlgorithmForStream.h"

/** Parametes for OpenCLRidgeDetector.
 * Only paramter to set is sigma - gain to output pixel.
 *
class OpenCLRidgeDetectorParams : public OpenCLAlgorithmParams
{
  float sigma;
  friend class OpenCLRidgeDetector;

public:
  **
   * Set gain.
   * @param gain usigned int.
   *
  void setSigma(float sigma);
};
*/

/** Algoritm performs Laplacian on image.
 * 
 */
class OpenCLRidgeDetector : public OpenCL2DTo2DImageAlgorithmForStream
{
public:
  OpenCLRidgeDetector(void);
  ~OpenCLRidgeDetector(void);

  //from OpenCLAlgorithm
  //void setParams(const OpenCLAlgorithmParams & params);
  //void setParams(const OpenCLRidgeDetectorParams & params);
  //void run(const unsigned char * data_input, size_t di_size, unsigned char * data_output, size_t do_size);
  //void setKernelArgs(size_t di_size, size_t do_size);
  void obtainAdditionalOutput();
  
  void releaseMem();

protected:
  //from OpenCLImageAlgorithm
  void copyDataToGPUStream();
  void setKernelArgsForStream();

  void *additionalOutput() const;

private:
  cl_mem additional_output_image_memory;

  void * output;
  size_t output_size;

  void clearOutput();
};

