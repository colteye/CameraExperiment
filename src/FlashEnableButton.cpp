#include "FlashEnableButton.h"

#define FLASH_ENABLE_LED 4

FlashEnableButton::FlashEnableButton(int g) : GPIOButton(g)
{
    pinMode(FLASH_ENABLE_LED, OUTPUT);
    digitalWrite(FLASH_ENABLE_LED, LOW);
}

void FlashEnableButton::onClick()
{
    puts("swag");
    if (digitalRead(FLASH_ENABLE_LED) == LOW) digitalWrite(FLASH_ENABLE_LED, HIGH);
    else digitalWrite(FLASH_ENABLE_LED, LOW);
}
