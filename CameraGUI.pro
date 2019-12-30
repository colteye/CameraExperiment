#SOURCES = src/CameraSensor.cpp src/CameraScreen.cpp src/CameraControl.cpp src/main.cpp 
#HEADERS = src/CameraSensor.h src/CameraScreen.h src/CameraControl.h

SOURCES = src/Event.cpp src/EventHandler.cpp src/BaseEventSystem.cpp src/CObject.cpp src/GPIOButton.cpp src/FlashEnableButton.cpp src/main.cpp
HEADERS = src/Event.h src/EventHandler.h src/BaseEventSystem.h src/CObject.h src/GPIOButton.h src/FlashEnableButton.h

LIBS += -lwiringPi

QT += gui widgets
CONFIG += qt warn_on release
