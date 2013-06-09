#pragma once

#include "OpenCLImageCommon.h"

/** Exception for OpenCL3DTo3DImageAlgorithm
 * 
 */
class OpenCL2DTo2DImageException : public OpenCLException
{
public:

  OpenCL2DTo2DImageException(std::string m, int e = 0) : OpenCLException(m, e)
  {
  }
};

class OpenCL2DTo2DImageAlgorithm : public virtual OpenCLImageCommon
{
public:
  /** 
   * Default constructor.
   */
  OpenCL2DTo2DImageAlgorithm(void);
    
  /**
   * Destructor.
   */
  ~OpenCL2DTo2DImageAlgorithm(void);

   /**
   * Set 2D and 2D image size. For 2D images only width and height is relevatnt.
   * @param w Image width.
   * @param h Image height.
   */
  void setDataSize(size_t w, size_t h);

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
