#include <signal.h>
#include <wiringPi.h>

#define FLASH_LED 1
#define FLASH_ENABLE_LED 4
#define FLASH_ENABLE_BUTTON 5
#define CAPTURE_BUTTON 6

class CameraControl
{
public:
    int initialize();
    void controlLoop();

protected:
    int pastStates[2], currentStates[2];
    
    static void setAllLow();
    static void interruptHandler(const int signal);
    int checkButtonPress(int gpio, int pastStatus, int currentStatus);
    void toggleGPIO(int gpio);
};
