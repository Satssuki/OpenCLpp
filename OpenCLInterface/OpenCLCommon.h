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
   * Set device to algorithm.
   * @param device OpenCLDevice to set.
   */
  void setDevice(const OpenCLDevice & dev);
  
  /**
   * Creates kernel from members. If file name is specified it uses file to get kernel source.
   * If not it tries to use source stored in std::string. If none of this option available it's throws exception.
   */
  void createKernel();
  
  /**
   * Run kernel.
   * @param work_dim Dimensions of data processed.
   * @param global_work_offset Work offset (where to start in regarding input pointer).
   * @param global_work_size Work size (can be image size).
   * @param local_work_size Local work size (how big data one computing unit is processing in time).
   * @param num_events_in_wait_list Put 0.
   */
  void enqueueNDRangeKernelWithTimeMeasurment(cl_uint work_dim, size_t * global_work_offset, const size_t *global_work_size, const size_t *local_work_size, cl_uint num_events_in_wait_list);

  /**
   * Get time consumed by kernel.
   * @return Time in ms in double.
   */  
  double getTime() const
  {
    return time;
  }

  
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

  /** time consumed by kernel
  */
  double time;

  /** device
  */
  OpenCLDevice device;

  /** cl_program 
  */    
  cl_program program;  

  /** cl_kernel
  */
  cl_kernel kernel;
  
  /** cl_context 
   */
  cl_context context;
  
  /** cl_command_queue
   */
  cl_command_queue command_queue;

private:
  void setDevice();
};

