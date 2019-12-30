#include "GPIOButton.h"

GPIOButton::GPIOButton(int g)
{
    gpio = g;
    pinMode(gpio, INPUT);
    digitalWrite(gpio, LOW);
    pastStatus = LOW;
}

void GPIOButton::onStart() { }

void GPIOButton::perFrame()
{
    currentStatus = digitalRead(gpio);
    if (checkClick(gpio, pastStatus, currentStatus) == 1) onClick();
    pastStatus = currentStatus;
}

void GPIOButton::onClose() { }

int GPIOButton::checkClick(int gpio, int pastStatus, int currentStatus)
{
    if (pastStatus != currentStatus && digitalRead(gpio) == 1) return 1;
    else return 0;
}

