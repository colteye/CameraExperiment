#ifndef CAMERACONTROL_H_
#define CAMERACONTROL_H_

#include <signal.h>
#include <wiringPi.h>
#include "CameraSensor.h"

#define STREAM_MODE 0
#define VIEW_MODE 1

#define FLASH_LED 1
#define FLASH_ENABLE_LED 4
#define FLASH_ENABLE_BUTTON 5
#define CAPTURE_BUTTON 6
#define MODE_BUTTON 26

class CameraControl
{
public:
    int getMode();
    int initialize(CameraSensor *cs);
    void controlLoop();

protected:
    CameraSensor *sensor;
    int flashEnabled, mode;
    int pastStates[3], currentStates[3];

    static void setAllLow();
    static void interruptHandler(const int signal);
    int checkButtonPress(int gpio, int pastStatus, int currentStatus);
    int toggleGPIO(int gpio);
};

#endif
