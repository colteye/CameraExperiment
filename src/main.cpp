#include <QApplication>
#include "CameraSensor.h"
#include "CameraScreen.h"

#include <wiringPi.h>
#include "FlashEnableButton.h"
#include "BaseEventSystem.h"

#define FLASH_ENABLE_BUTTON 5

int main(int argc, char *argv[]) {

QApplication app(argc, argv); // Init GUI app

wiringPiSetup(); // Needed for GPIO
BaseEventSystem* baseSystem = new BaseEventSystem(); // Basic Event System

// All objects must be constructed + registered before starting the control flow.
FlashEnableButton flashEnable = FlashEnableButton(FLASH_ENABLE_BUTTON);
CameraSensor sensor;

// Registering CObjects.
sensor.registerObject(baseSystem);
flashEnable.registerObject(baseSystem);

// Execute GUI, start control flow.
baseSystem->startEvent();
return app.exec();
}
