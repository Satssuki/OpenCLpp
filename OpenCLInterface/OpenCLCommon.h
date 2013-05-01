#pragma once

#include "OpenCLDevice.h"

#include <string>

/** It's for common opeartions which every algorithm has to do.
 * It contains creating kernel.
 */
class OpenCLCommon
{
public:
  /**
   * Default constructor.
   */
  OpenCLCommon(void);
  
  /**
   * Destructor.
   */
  ~OpenCLCommon(void);
  
  /**
   * Creates kernel from members. If file name is specified it uses file to get kernel source.
   * If not it tries to use source stored in std::string. If none of this option available it's throws exception.
   */
  void createKernel();
  
protected:
  /** file name with kernel source
   */
  std::string source_filename;
  
  /** kernel source itself
   */
  std::string source;

  /** kernel name
  */
  std::string kernel_name;

  /** device
  */
  OpenCLDevice device;

  /** cl_program 
  */    
  cl_program program;  

  /** cl_kernel
  */
  cl_kernel kernel;
};

