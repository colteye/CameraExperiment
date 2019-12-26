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

#define STREAM_WIDTH 640
#define STREAM_HEIGHT 480

#define CAPTURE_WIDTH 3280
#define CAPTURE_HEIGHT 2464

#define FRAMES_PER_SEC 60

class CameraSensor
{
public:
    void *buffer; //image buffer for capturing
    int bufferLen; //length of buffer

    CameraSensor();
    int streamFrame();
    int takePicture();

protected:
    int fd; //file descriptor

    int xioctl(int fd, int request, void *arg);
    int initializeSensor(int width, int height, unsigned int pixFormat);
    int setupSensor(int width, int height, unsigned int pixFormat);
    int closeSensor();
    int initBufferCamera();
    int numFilesDir(char *path);
};

#endif


