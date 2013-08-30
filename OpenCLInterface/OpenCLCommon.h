#pragma once

#include "OpenCLDevice.h"
#include "OpenCLAlgorithmParams.h"

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
  virtual ~OpenCLCommon(void);
  
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
  
  /**
   * Prepare algorithm. Data size need to be set. If not there will be error.
   */
  void prepare();
  
  /**
   * Process data with algorithm.
   * @param data_input Pointer to input data.
   * @param data_output Pointer to output data.
   */
  virtual void processData(const void * data_input, void * data_output) = 0;

  virtual void setParams(const OpenCLAlgorithmParams & params);
  
protected:
  
  /**
   * Set arguments 0(input data) and 1(output data) for kernel.
   */
  virtual void setIOArguments() = 0;
  
  /**
   * Set other sarguments (2 and above) for kernel. It's algorithm specific arguments.
   */
  virtual void setOtherArguments() = 0;
  
  /**
   * Sets kernel nr argument.
   * @param nr Argument number.
   * @param argument Pointer to argument pointer.
   * @param size Size of argument (default is sizeof(cl_mem)).
   * @return Returns 0 in success and OpenCL error number otherwise.
   */
  cl_int setKernelArg(int nr, const void * argument, size_t size = sizeof(cl_mem));
  
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
  
  /** If algorithm was prepared
   */
  bool prepared;

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

  /** defines to cl kernel code
  */
  std::string defines;

private:
  void setDevice();
};

