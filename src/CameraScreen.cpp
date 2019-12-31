#include "CameraScreen.h"

#define SCALE_FACTOR 1.5

CameraScreen::CameraScreen(QWidget *parent) : QWidget(parent)
{
    label = new QLabel("camera frame", this);
    setWindowFlags( Qt::Window | Qt::FramelessWindowHint);
}

void CameraScreen::setDimensions(int w, int h)
{
    newWidth = w * SCALE_FACTOR;
    newHeight = h * SCALE_FACTOR;
    label->setGeometry(0, 0, newWidth, newHeight);
    resize(newWidth, newHeight);
}

void CameraScreen::newFrame(void* buffer, int bufferLen)
{
    QPixmap frame = QPixmap();
    frame.loadFromData((const uchar *)buffer, bufferLen, 0, Qt::AutoColor);
    label->setPixmap(frame.scaled(newWidth, newHeight));
    label->repaint();
}
