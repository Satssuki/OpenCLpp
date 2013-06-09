#pragma once
#include "OpenCL2DTo2DImageAlgorithmForStream.h"

/** Parametes for OpenCLCornerDetector.
 * Only paramter to set is sigma - gain to output pixel.
 *
class OpenCLCornerDetectorParams : public OpenCLAlgorithmParams
{
  float sigma;
  friend class OpenCLCornerDetector;

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
class OpenCLCornerDetector : public OpenCL2DTo2DImageAlgorithmForStream
{
public:
  OpenCLCornerDetector(void);
  ~OpenCLCornerDetector(void);

  //from OpenCLAlgorithm
  void setParams(const OpenCLAlgorithmParams & params);
  //void setParams(const OpenCLCornerDetectorParams & params);
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

