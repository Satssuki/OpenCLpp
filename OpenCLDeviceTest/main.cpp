#include <gtest/gtest.h>

#include <OpenCLDevice.h>

class DeviceParameters : public ::testing::Test
{
protected:
  void getDevs()
  {
    devs = OpenCLDevice::getDevices();
  }
  void SetUp()
  {
    getDevs();
  }
  std::list<OpenCLDevice> devs;

  OpenCLDevice empty_device;
};

class DeviceContext : public DeviceParameters
{
};

class CommandQueue : public DeviceParameters
{
};

class IsValidTest: public DeviceParameters
{
};

class BuildProgram : public DeviceParameters
{
protected:
  void SetUp()
  {
    getDevs();
    source = "\n" \
"__kernel void square(                                                       \n" \
"   __global float* input,                                              \n" \
"   __global float* output,                                             \n" \
"   const unsigned int count)                                           \n" \
"{                                                                      \n" \
"   int i = get_global_id(0);                                           \n" \
"   if(i < count)                                                       \n" \
"       output[i] = input[i] * input[i];                                \n" \
"}                                                                      \n" \
"\n";
    filename = "test.cl";
  }
  std::string filename;
  std::string source;
};

TEST(QueryingPlatforms, NumberOfDevices)
{
  EXPECT_GT(OpenCLDevice::getDevices().size(), (unsigned int)0);
}

TEST_F(DeviceParameters, QueryNameNoThrow)
{
  ASSERT_GT(devs.size(), (unsigned int)0);
  EXPECT_NO_THROW(devs.front().getName());
}

TEST_F(DeviceParameters, QueryNameThrow)
{
 EXPECT_THROW(empty_device.getName(), OpenCLDeviceException);
}

TEST_F(DeviceParameters, QueryPlatformNameNoThrow)
{
  ASSERT_GT(devs.size(), (unsigned int)0);
  EXPECT_NO_THROW(devs.front().getName());
}

TEST_F(DeviceParameters, QueryPlatformNameThrow)
{
  EXPECT_THROW(empty_device.getPlatformName(), OpenCLDeviceException);
}

TEST_F(DeviceContext, GetContextNoThrow)
{
  ASSERT_GT(devs.size(), (unsigned int)0);
  EXPECT_NO_THROW(devs.front().getContext());
}

TEST_F(CommandQueue, GetCommandQueueNoThrow)
{
  ASSERT_GT(devs.size(), (unsigned int)0);
  EXPECT_NO_THROW(devs.front().getCommandQueue());
}

TEST_F(CommandQueue, GetCommandQueueThrow)
{
  EXPECT_THROW(empty_device.getCommandQueue(), OpenCLDeviceException);
}

TEST_F(BuildProgram, BuildFromFileNoThrow)
{
  ASSERT_GT(devs.size(), (unsigned int)0);
  EXPECT_NO_THROW(devs.front().createAndBuildProgramFromFile(filename));
}

TEST_F(BuildProgram, BuildFromFileThrow)
{
  EXPECT_THROW(empty_device.createAndBuildProgramFromFile(filename), OpenCLDeviceException);
}

TEST_F(BuildProgram, BuildFromSourceNoThrow)
{
  ASSERT_GT(devs.size(), (unsigned int)0);
  EXPECT_NO_THROW(devs.front().createAndBuildProgramFromSource(source));
}

TEST_F(BuildProgram, BuildFromSourceThrow)
{
  EXPECT_THROW(empty_device.createAndBuildProgramFromSource(source), OpenCLDeviceException);
}

TEST_F(IsValidTest, ValidDevice)
{
  EXPECT_TRUE(devs.front().isValid());
}

TEST_F(IsValidTest, InvalidDevice)
{
  EXPECT_FALSE(empty_device.isValid());
}

int main(int argc, char** argv) 
{ 
    testing::InitGoogleTest(&argc, argv); 
    RUN_ALL_TESTS(); 
}
