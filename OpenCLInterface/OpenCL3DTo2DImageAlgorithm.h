#pragma once
#include "OpenCLCommon.h"

/** Exception for OpenCL3DTo3DImageAlgorithm
 * 
 */
class OpenCL3DTo2DImageException : public OpenCLException
{
public:

  OpenCL3DTo2DImageException(std::string m, int e = 0) : OpenCLException(m, e)
  {
  }
};

/** Class for algorithms that support reading 3D image and stores data in 2D image.
 * 
 */
class OpenCL3DTo2DImageAlgorithm : public OpenCLCommon
{
public:
  /** 
   * Default constructor.
   */
  OpenCL3DTo2DImageAlgorithm(void);
  
  /**
   * Destructor.
   */
  ~OpenCL3DTo2DImageAlgorithm(void);
  
  /**
   * Set 3D and 2D image size. For 2D images only width and height is relevatnt.
   * @param w Image width.
   * @param h Image height.
   * @param d Image depth.
   */
  void setDataSize(size_t w, size_t h, size_t d);
};

