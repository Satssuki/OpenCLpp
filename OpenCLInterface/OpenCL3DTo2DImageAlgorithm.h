#pragma once
#include "OpenCLImageCommon.h"

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
class OpenCL3DTo2DImageAlgorithm : public virtual OpenCLImageCommon
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

