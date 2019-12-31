#ifndef GPIOBUTTON_H_
#define GPIOBUTTON_H_

#include <wiringPi.h>
#include "CObject.h"

class GPIOButton : public CObject
{
public:
    virtual void onClick() = 0;

protected:
    int gpio;
    GPIOButton(int g);
    void perFrame();

private:
    int pastStatus, currentStatus;
    int checkClick(int gpio, int pastStatus, int currentStatus);
};
#endif
