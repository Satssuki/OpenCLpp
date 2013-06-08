#pragma once
#include "OpenCLAlgorithm.h"

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
class OpenCLEdgeDetector : public OpenCLImageAlgorithm
{
public:
  OpenCLEdgeDetector(void);
  ~OpenCLEdgeDetector(void);

  //from OpenCLAlgorithm
  void setParams(const OpenCLAlgorithmParams & params);
  //void setParams(const OpenCLEdgeDetectorParams & params);
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
