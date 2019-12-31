#ifndef CAMERASENSOR_H_
#define CAMERASENSOR_H_

#include <errno.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <dirent.h>
#include "CObject.h"
#include "CameraScreen.h"

#define IMAGE_PATH "/home/pi/Pictures/"

#define STREAM_WIDTH 480
#define STREAM_HEIGHT 320

#define CAPTURE_WIDTH 3280
#define CAPTURE_HEIGHT 2464

class CameraSensor : public CObject
{
public:
    CameraSensor();
    void onStart();
    void perFrame();
    void onClose();
    void onCapture();

protected:
    CameraScreen screen;
    int fd; //file descriptor
    void *buffer; //image buffer for capturing
    int bufferLen; //length of buffer

    int initializeSensor(int width, int height, unsigned int pixFormat);
    int closeSensor();

    int startStreaming();
    int streamFrame();
    int takePicture();

    int xioctl(int fd, int request, void *arg);
    int setupSensor(int width, int height, unsigned int pixFormat);
    int initBufferCamera();
    int writeImage(void *buffer, int bufferLen, const char *path);
    int numFilesDir(const char *path);
};

#endif
