#include <cstring>
#include "CameraControl.h"

int CameraControl::initialize(CameraSensor *cs)
{
    signal(SIGINT, CameraControl::interruptHandler);

    if (-1 == wiringPiSetup()) return 1;

    pinMode(FLASH_LED, OUTPUT);
    pinMode(FLASH_ENABLE_LED, OUTPUT);
    pinMode(FLASH_ENABLE_BUTTON, INPUT);
    pinMode(CAPTURE_BUTTON, INPUT);

    flashEnabled = 0;
    CameraControl::setAllLow();

    sensor = cs;

    pastStates[0] = digitalRead(CAPTURE_BUTTON);
    pastStates[1] = digitalRead(FLASH_ENABLE_BUTTON);
 
    return 0;
}

void CameraControl::controlLoop()
{
    currentStates[0] = digitalRead(CAPTURE_BUTTON);
    currentStates[1] = digitalRead(FLASH_ENABLE_BUTTON);

    if (checkButtonPress(CAPTURE_BUTTON, pastStates[0], currentStates[0]) == 1)
    {
        if (flashEnabled == 1)
        {
           digitalWrite(FLASH_LED, HIGH);
           delay(200);
           digitalWrite(FLASH_LED, LOW);
        }
    }

    if (checkButtonPress(FLASH_ENABLE_BUTTON, pastStates[1], currentStates[1]) == 1)
    { 
        flashEnabled = toggleGPIO(FLASH_ENABLE_LED);
    }

    memcpy(pastStates, currentStates, sizeof(pastStates)); 
}

void CameraControl::setAllLow()
{
    digitalWrite(FLASH_LED, LOW);
    digitalWrite(FLASH_ENABLE_LED, LOW);
    digitalWrite(FLASH_ENABLE_BUTTON, LOW);
    digitalWrite(CAPTURE_BUTTON, LOW);
}

void CameraControl::interruptHandler(const int signal)
{
    CameraControl::setAllLow();
}

int CameraControl::checkButtonPress(int gpio, int pastStatus, int currentStatus)
{
    if (pastStatus != currentStatus && digitalRead(gpio) == 1) return 1;
    else return 0;
}

int CameraControl::toggleGPIO(int gpio)
{
    if (digitalRead(gpio) == HIGH) 
    {
        digitalWrite(gpio, LOW); 
        return 0;
    }
    else digitalWrite(gpio, HIGH);
    { 
        return 1;
    }
}
