#ifndef _STROBE_H_
#define _STROBE_H_

#include <dc1394/dc1394.h>
#include "camera1394/Camera1394Config.h"
typedef camera1394::Camera1394Config Config;

/*
 * This is a 1394 strobe interface, following the Trigger interface
 */

class SimpleStrobe
{
  private:
    dc1394camera_t *camera_;

  public:
    /* Constructor */
    SimpleStrobe(dc1394camera_t *camera):
      camera_(camera)
    {};

    bool strobeOn();
    bool strobeOff();

    bool reconfigure(Config *newconfig);
    bool initialize(Config *newconfig);
};
#endif // _STROBE_H_
