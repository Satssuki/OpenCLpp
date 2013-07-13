#pragma once
#include "OpenCL2DTo2DImageAlgorithmForStream.h"

/** Parametes for OpenCLEdgeDetector.
 * Only paramter to set is sigma - gain to output pixel.
 *
class OpenCLEdgeDetectorParams : public OpenCLAlgorithmParams
{
  float sigma;
  friend class OpenCLEdgeDetector;

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
class OpenCLEdgeDetector : public OpenCL2DTo2DImageAlgorithmForStream
{
public:
  OpenCLEdgeDetector(void);
  ~OpenCLEdgeDetector(void);

  //from OpenCLAlgorithm
  //void setParams(const OpenCLAlgorithmParams & params);
  //void setParams(const OpenCLEdgeDetectorParams & params);
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

