#ifndef FLASH_ENABLE_BUTTON_H_
#define FLASH_ENABLE_BUTTON_H_

#include "GPIOButton.h"

class FlashEnableButton : public GPIOButton
{
public:
    FlashEnableButton(int g);
    void onClick();
};
#endif
