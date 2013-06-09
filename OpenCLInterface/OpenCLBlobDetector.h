#pragma once
#include "OpenCL2DTo2DImageAlgorithmForStream.h"

/** Parametes for OpenCLBlobDetector.
 * Only paramter to set is sigma - gain to output pixel.
 *
class OpenCLBlobDetectorParams : public OpenCLAlgorithmParams
{
  float sigma;
  friend class OpenCLBlobDetector;

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
class OpenCLBlobDetector : public OpenCL2DTo2DImageAlgorithmForStream
{
public:
  OpenCLBlobDetector(void);
  ~OpenCLBlobDetector(void);

  //from OpenCLAlgorithm
  void setParams(const OpenCLAlgorithmParams & params);
  //void setParams(const OpenCLBlobDetectorParams & params);
  void run(const unsigned char * data_input, size_t di_size, unsigned char * data_output, size_t do_size);
  void setKernelArgs(size_t di_size, size_t do_size);
  
  void releaseMem();

protected:
  //from OpenCLImageAlgorithm
  void copyDataToGPUStream();
  void setKernelArgsForStream();

private:
  //private stuff
};

