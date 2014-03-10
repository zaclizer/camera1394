#include "simple_strobe.h"
#include <ros/ros.h>

bool SimpleStrobe::strobeOn()
{
  dc1394error_t err = dc1394_set_PIO_register(camera_, uint64_t(0x0008), uint32_t(0xE0000000));
  err = dc1394_set_strobe_register(camera_, uint64_t(0x0200), uint32_t(0x83200400));
  if (err != DC1394_SUCCESS)
  {
    ROS_ERROR("strobeOn() failed: %d", err);
    return false;
  }
  return true;
}

bool SimpleStrobe::strobeOff()
{
  dc1394error_t err = dc1394_set_strobe_register(camera_, uint64_t(0x0200), uint32_t(0x00000000));
  if (err != DC1394_SUCCESS)
  {
    ROS_ERROR("strobeOff() failed: %d", err);
    return false;
  }
  return true;
}

bool SimpleStrobe::reconfigure(Config *newconfig)
{
  ROS_INFO("Config->strobe: %d", newconfig->strobe);
  if (newconfig->strobe)
  {
    ROS_INFO("strobeOn()");
    strobeOn();
  }
  else
  {
    ROS_INFO("strobeOff()");
    strobeOff();
  }
}

bool SimpleStrobe::initialize(Config *newconfig)
{
  ROS_INFO("[%016lx] has strobe support", camera_->guid);

  // configure strobe features
  return reconfigure(newconfig);
}
