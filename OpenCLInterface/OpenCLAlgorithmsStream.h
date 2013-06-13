#pragma once

//#include "OpenCLAlgorithm.h"
#include "OpenCLAlgorithmForStream.h"
#include "OpenCLException.h"
#include "OpenCLDevice.h"

#include <list>

struct OpenCLAlgorithmsStreamException : public OpenCLException
{
  OpenCLAlgorithmsStreamException(std::string m, int e = 0) : OpenCLException(m,e) {}
};

/**
 * @brief Class for creating algorithms streams.
 * 
 * It can be used with algorithms that use cl_image_2d. Algorithm must have first parameter as input image and second parameter as output image. Other parameters can be use manually and freely in copyDataToGPUStream and setKernelArgsForStream.
 * Input for next algorithm must be same as output for previous algorithm.
 */
class OpenCLAlgorithmsStream
{
public:
  OpenCLAlgorithmsStream(void);
  ~OpenCLAlgorithmsStream(void);

private:
  OpenCLAlgorithmsStream(const OpenCLAlgorithmsStream &);

public:
  /**
   * Add algorithm to stream on last position. Throws OpenCLAlgorithmsStreamException if input is differ from output of last algorithm on list.
   * @param al Algorithm to add.
   */
  void pushAlgorithm(OpenCLAlgorithmForStream * al);
  /**
   * Removes all algorithms from stream.
   */
  void clearAlgorithms();

  /**
   * Set size of image.
   * @param w Width.
   * @param h Height.
   */
  void setDataSize(size_t w, size_t h);
  /**
   * Prepare algorithms for execution.
   */
  void prepare();
  /**
   * Execute stream. This function executes all algorithms in stream in order. Must call prepare and setDevice before.
   * @param data_input Pointer to data input.
   * @param data_output Pointer to data output.
   * @param from Number of algorithm form which to start.
   */
  void processImage(const void * data_input, void * data_output, unsigned int from = 0);
  /**
   * Set device for executing.
   * @param d Device.
   */
  void setDevice(OpenCLDevice & d);
  /**
   * Get time consumed on execution all algorithms in stream on last run.
   * @return Time in ms.
   */
  double getTime();

  /**
   * Returns additional output data from last algorithm.
   * @return Returs void * with data if last algorithm provide additional output, nullptr otherwise.
   */
  void* getLastAlgorithmAdditionalOutput() const;
  
private:
  OpenCLDevice device;
  double time;


  std::list<OpenCLAlgorithmForStream*> algorithms;
  size_t width, height;
  cl_mem input, output;
  std::list<cl_mem> mems;
  cl_context context;
  cl_command_queue command_queue;

  bool prepared;
};


