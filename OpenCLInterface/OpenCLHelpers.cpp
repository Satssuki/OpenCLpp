#include <iostream>
#include <string>
#include <list>

#include "OpenCLHelpers.h"
#include "OpenCLDevice.h"


void list_devices ()
{
  try
    {
      std::list<OpenCLDevice> devs = OpenCLDevice::getDevices ();
      std::cout << "Devices found: " << devs.size () << "\n";
      if (!devs.empty ())
        {
          std::cout << "Platform: " << devs.front ().getPlatformName () << "\n";
          std::cout << "Device: " << devs.front ().getName () << "\n";
          devs.front ().getCommandQueue ();
        }
    }
  catch (OpenCLDeviceException e)
    {
      std::cout << e.getFullMessage () << "\n";
    }
}

std::string getImageChannelFormat (cl_int image)
{
  switch (image)
    {
      /* cl_channel_type */
    case CL_SNORM_INT8:
      return "CL_SNORM_INT8";
    case CL_SNORM_INT16:
      return "CL_SNORM_INT16";
    case CL_UNORM_INT8:
      return "CL_UNORM_INT8";
    case CL_UNORM_INT16:
      return "CL_UNORM_INT16";
    case CL_UNORM_SHORT_565:
      return "CL_UNORM_SHORT_565";
    case CL_UNORM_SHORT_555:
      return "CL_UNORM_SHORT_555";
    case CL_UNORM_INT_101010:
      return "CL_UNORM_INT_101010";
    case CL_SIGNED_INT8:
      return "CL_SIGNED_INT8";
    case CL_SIGNED_INT16:
      return "CL_SIGNED_INT16";
    case CL_SIGNED_INT32:
      return "CL_SIGNED_INT32";
    case CL_UNSIGNED_INT8:
      return "CL_UNSIGNED_INT8";
    case CL_UNSIGNED_INT16:
      return "CL_UNSIGNED_INT16";
    case CL_UNSIGNED_INT32:
      return "CL_UNSIGNED_INT32";
    case CL_HALF_FLOAT:
      return "CL_HALF_FLOAT";
    case CL_FLOAT:
      return "CL_FLOAT";
    default:
      return "WRONG";
    }
}

std::string getImageChannelOrder (cl_int image)
{
  switch (image)
    {
    case CL_R:
      return "CL_R";
    case CL_A:
      return "CL_A";
    case CL_RG:
      return "CL_RG";
    case CL_RA:
      return "CL_RA";
    case CL_RGB:
      return "CL_RGB";
    case CL_RGBA:
      return "CL_RGBA";
    case CL_BGRA:
      return "CL_BGRA";
    case CL_ARGB:
      return "CL_ARGB";
    case CL_INTENSITY:
      return "CL_INTENSITY";
    case CL_LUMINANCE:
      return "CL_LUMINANCE";
    case CL_Rx:
      return "CL_Rx";
    case CL_RGx:
      return "CL_RGx";
    case CL_RGBx:
      return "CL_RGBx";
    default:
      return "WRONG";
    }
}

void list_supported_image_formats ()
{
  OpenCLDevice d = OpenCLDevice::getDevices ().front ();
  cl_image_format formats[100];
  cl_uint returned;
  clGetSupportedImageFormats (d.getContext (), CL_MEM_READ_ONLY, CL_MEM_OBJECT_IMAGE2D, 100, formats, &returned);
  std::cout << returned << "\n";
  for (unsigned int i = 0; i < returned; ++i)
    {
      std::cout << "Format: " << getImageChannelOrder(formats[i].image_channel_order) << " , " << getImageChannelFormat(formats[i].image_channel_data_type) << "\n";
    }
}