#include <errno.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

class CameraSensor
{
public:
    void *buffer; //image buffer for capturing
    int bufferLen; //length of buffer

    int initialize(int width, int height);
    int captureImage();
protected:
    int fd; //file descriptor

    int xioctl(int fd, int request, void *arg);
    int setup(int width, int height);
    int initBufferCamera();
};


