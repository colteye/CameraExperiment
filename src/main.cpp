#include <QApplication>
#include "CameraScreen.h"

#include <wiringPi.h>
#include "FlashEnableButton.h"
#include "BaseEventSystem.h"

#define FLASH_ENABLE_BUTTON 5

int main(int argc, char *argv[]) {

wiringPiSetup(); // Needed for GPIO
BaseEventSystem* baseSystem = new BaseEventSystem(); // Basic Event System

// All objects must be registered before starting the control flow.
FlashEnableButton flashEnable = FlashEnableButton(FLASH_ENABLE_BUTTON);
flashEnable.registerObject(baseSystem);

baseSystem->baseControlFlow();

delete baseSystem;

/*    QApplication app(argc, argv);
    CameraScreen screen; 
    screen.show();

    return app.exec();  */
return 0;
}
