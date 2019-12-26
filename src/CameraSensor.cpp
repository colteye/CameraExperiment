#include "CameraSensor.h"

CameraSensor::CameraSensor()
{
    if (initializeSensor(STREAM_WIDTH, STREAM_HEIGHT, V4L2_PIX_FMT_MJPEG) == 1)
    {
        perror("Initializing Sensor");
    }
}

int CameraSensor::xioctl(int fd, int request, void *arg)
{
    int r;
    do r = ioctl (fd, request, arg);
    while (-1 == r && EINTR == errno);
    return r;
}

int CameraSensor::setupSensor(int width, int height, unsigned int pixFormat) 
{
    if (fd == -1)
    {
    // couldn't find capture device
        perror("Opening Video device");
        return 1;
    }


    struct v4l2_capability caps = {0};
    if (-1 == xioctl(fd, VIDIOC_QUERYCAP, &caps))
    {
        perror("Querying Capabilites");
        return 1;
    }

    struct v4l2_format fmt = {0};
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = width;
    fmt.fmt.pix.height = height;
    fmt.fmt.pix.pixelformat = pixFormat;
  //  fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_JPEG;
    fmt.fmt.pix.field = V4L2_FIELD_NONE;

    if (-1 == xioctl(fd, VIDIOC_S_FMT, &fmt))
    {
        perror("Setting Pixel Format");
        return 1;
    }
    return 0;
}

int CameraSensor::initBufferCamera() 
{
    struct v4l2_requestbuffers req = {0};
    req.count = 1;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if (-1 == xioctl(fd, VIDIOC_REQBUFS, &req))
    {
        perror("Requesting Buffer");
        return 1;
    }

    struct v4l2_buffer buf = {0};
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = 0;
    if(-1 == xioctl(fd, VIDIOC_QUERYBUF, &buf))
    {
        perror("Querying Buffer");
        return 1;
    }

    buffer = mmap(NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buf.m.offset);
    bufferLen = buf.length;

    if(-1 == xioctl(fd, VIDIOC_STREAMON, &buf.type))
    {
        perror("Start Capture");
        return 1;
    }
    return 0;
}

int CameraSensor::streamFrame() {
    struct v4l2_buffer buf = {0};
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = 0;
    if(-1 == xioctl(fd, VIDIOC_QBUF, &buf))
    {
        perror("Query Buffer");
        return 1;
    }

    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(fd, &fds);
    struct timeval tv = {0};
    tv.tv_sec = 2;
    int r = select(fd+1, &fds, NULL, NULL, &tv);
    if(-1 == r)
    {
        perror("Waiting for Frame");
        return 1;
    }

    if(-1 == xioctl(fd, VIDIOC_DQBUF, &buf))
    {
        perror("Retrieving Frame");
        return 1;
    }
    return 0;
}

int CameraSensor::initializeSensor(int width, int height, unsigned int pixFormat)
{
   fd = open("/dev/video0", O_RDWR);
   if (setupSensor(width, height, pixFormat) == 1)
   {
        perror("Setting up");
        return 1;
   }

   if (initBufferCamera() == 1)
   {
        perror("initializing buffer and camera");
        return 1;
   }
   return 0;
}

int CameraSensor::closeSensor()
{
    if (munmap(buffer, bufferLen) == -1)
    {
        perror("Unmapping Buffer");
        return 1;
    }

    enum v4l2_buf_type type;
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if(-1 == xioctl(fd, VIDIOC_STREAMOFF, &type))
    {
        perror("Stop Capture");
        return 1;
    }

    if (close(fd) == -1)
    {
        perror("Closing Device");
        return 1;
    }
    return 0;
}

int CameraSensor::takePicture()
{
    if (closeSensor() == 1)
    {
        perror("Closing Device");
        return 1;
    }

    if (initializeSensor(CAPTURE_WIDTH, CAPTURE_HEIGHT, V4L2_PIX_FMT_JPEG) == 1)
    {
        perror("Initializing for Photo");
        return 1;
    }

    if (streamFrame() == 1)
    {
        perror("Capturing Frame");
        return 1;
    }

    char imagePath[] = "/home/pi/Pictures/";
    int num = numFilesDir(imagePath);
    char finalDir [1024];
    int result = snprintf(finalDir, 1024, "%simage_%d.jpg", imagePath, num);

    if (result > 0 && result < 1024)
    {
        int filefd = open(finalDir, O_WRONLY | O_CREAT | O_TRUNC,
        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

        write(filefd, buffer, bufferLen);

        if (close(filefd) == -1)
        {
            perror("Closing Image");
            return 1;
        }
    }
    else 
    {
        perror("Creating Path");
        return 1;
    }

    if (closeSensor() == 1)
    {
        perror("Closing Device");
        return 1;
    }

    if (initializeSensor(STREAM_WIDTH, STREAM_HEIGHT, V4L2_PIX_FMT_MJPEG) == 1)
    {
        perror("Reinitializing Stream");
        return 1;
    }
    return 0;
}

int CameraSensor::numFilesDir(char *path)
{
    struct dirent *de;  // Pointer for directory entry
    int numFiles = 0;
    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir(path);

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        perror("Could not open current directory" );
        return -1;
    }

    while ((de = readdir(dr)) != NULL)
         numFiles++;

    closedir(dr);
    return numFiles;
}
