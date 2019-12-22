SOURCES = src/CameraSensor.cpp src/CameraScreen.cpp src/CameraControl.cpp src/main.cpp 
HEADERS = src/CameraSensor.h src/CameraScreen.h src/CameraControl.h
LIBS += -lwiringPi

QT += gui widgets
CONFIG += qt warn_on release
