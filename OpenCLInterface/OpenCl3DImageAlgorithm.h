#pragma once

#include "OpenCLDevice.h"
#include "OpenCLException.h"
#include "OpenCLImageCommon.h"

/** Exception for OpenCL3DImageAlgorithm 
 * 
 */
class OpenCL3DImageException : public OpenCLException
{
public:

  OpenCL3DImageException(std::string m, int e = 0) : OpenCLException(m, e)
  {
  }
};

/** Class for algorithms manipulating 3D images.
 * Simple framework. It does not work with many NVIDIA devices, because they not support writing 3D images.
 * Should work on some AMD devices.
 */
class OpenCL3DImageAlgorithm : public OpenCLImageCommon
{
public:
  /**
   * Default contructor.
   */
  OpenCL3DImageAlgorithm(void);

  /**
   * Destructor.
   */
  ~OpenCL3DImageAlgorithm(void);

  /**
   * Set 3D image size.
   * @param w Image width.
   * @param h Image height.
   * @param d Image depth.
   */
  void setDataSize(size_t w, size_t h, size_t d);

  /**
   * Get gime consumed on algorithm execution.
   * @return Time in ms.
   */
  double getTime();
protected:
  /**
   * set IO args.
   */
  void setIOArguments();
  
  /**
   * set other args.
   */
  void setOtherArguments();
  
};
