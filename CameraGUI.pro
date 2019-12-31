SOURCES = src/Event.cpp src/EventHandler.cpp src/BaseEventSystem.cpp src/CObject.cpp src/CameraScreen.cpp src/CameraSensor.cpp src/GPIOButton.cpp src/FlashEnableButton.cpp src/main.cpp
HEADERS = src/Event.h src/EventHandler.h src/BaseEventSystem.h src/CObject.h src/CameraScreen.h src/CameraSensor.h src/GPIOButton.h src/FlashEnableButton.h

LIBS += -lwiringPi

QT += gui widgets
CONFIG += qt warn_on release
