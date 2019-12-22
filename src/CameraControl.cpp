#include <cstring>
#include "CameraControl.h"

int CameraControl::initialize()
{
    signal(SIGINT, CameraControl::interruptHandler);

    if (-1 == wiringPiSetup()) return 1;

    pinMode(FLASH_LED, OUTPUT);
    pinMode(FLASH_ENABLE_LED, OUTPUT);
    pinMode(FLASH_ENABLE_BUTTON, INPUT);
    pinMode(CAPTURE_BUTTON, INPUT);

    CameraControl::setAllLow();

    pastStates[0] = digitalRead(CAPTURE_BUTTON);
    pastStates[1] = digitalRead(FLASH_ENABLE_BUTTON);
 
    return 0;
}

void CameraControl::controlLoop()
{
    currentStates[0] = digitalRead(CAPTURE_BUTTON);
    currentStates[1] = digitalRead(FLASH_ENABLE_BUTTON);

    if (checkButtonPress(FLASH_ENABLE_BUTTON, pastStates[1], currentStates[1]) == 1) 
        toggleGPIO(FLASH_ENABLE_LED);

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

void CameraControl::toggleGPIO(int gpio)
{
 if (digitalRead(gpio) == HIGH) digitalWrite(gpio, LOW);
 else digitalWrite(gpio, HIGH);
}
