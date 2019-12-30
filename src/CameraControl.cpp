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
    pinMode(MODE_BUTTON, INPUT);

    flashEnabled = 0;
    sensor = cs;
    mode = STREAM_MODE;

    pastStates[0] = digitalRead(CAPTURE_BUTTON);
    pastStates[1] = digitalRead(FLASH_ENABLE_BUTTON);
    pastStates[2] = digitalRead(MODE_BUTTON);

    CameraControl::setAllLow();

    return 0;
}

void CameraControl::controlLoop()
{
    // Set states
    currentStates[0] = digitalRead(CAPTURE_BUTTON);
    currentStates[1] = digitalRead(FLASH_ENABLE_BUTTON);
    currentStates[2] = digitalRead(MODE_BUTTON);

    // Check Capture Button
    if (checkButtonPress(CAPTURE_BUTTON, pastStates[0], currentStates[0]) == 1)
    {
        if (flashEnabled == 1)
        {
           digitalWrite(FLASH_LED, HIGH);
           sensor->takePicture();
           digitalWrite(FLASH_LED, LOW);
        }
        else sensor->takePicture();
    }

    // Check Flash Enable Button
    if (checkButtonPress(FLASH_ENABLE_BUTTON, pastStates[1], currentStates[1]) == 1)
    {
        flashEnabled = toggleGPIO(FLASH_ENABLE_LED);
    }

    // Check Mode button
    if (checkButtonPress(MODE_BUTTON, pastStates[2], currentStates[2]) == 1)
    {
        if (mode == STREAM_MODE)
        {
            sensor->closeSensor();
            mode = VIEW_MODE;
        }
        else
        {
            sensor->startStreaming();
            mode = STREAM_MODE;
        }
    }

    // Set current states to previous states.
    memcpy(pastStates, currentStates, sizeof(pastStates));
}

void CameraControl::setAllLow()
{
    digitalWrite(FLASH_LED, LOW);
    digitalWrite(FLASH_ENABLE_LED, LOW);
    digitalWrite(FLASH_ENABLE_BUTTON, LOW);
    digitalWrite(CAPTURE_BUTTON, LOW);
    digitalWrite(MODE_BUTTON, LOW);
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
    else
    {
        digitalWrite(gpio, HIGH);
        return 1;
    }
}

int CameraControl::getMode()
{
    return mode;
}
