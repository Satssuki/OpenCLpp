#include "OpenCL3DTo2DImageAlgorithm.h"


OpenCL3DTo2DImageAlgorithm::OpenCL3DTo2DImageAlgorithm(void) : OpenCLImageCommon()
{
  input_image_memory = output_image_memory = nullptr;
  width = height = depth = 0;
}


OpenCL3DTo2DImageAlgorithm::~OpenCL3DTo2DImageAlgorithm(void)
{
}
