#include "CameraScreen.h"
#include <time.h> 

CameraScreen::CameraScreen(QWidget *parent) : QWidget(parent)
{
    label = new QLabel("camera frame", this);
    label->setGeometry(0, 0, WIDTH, HEIGHT);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&CameraScreen::update));
    timer->start((int)(1000/FRAMES_PER_SEC));

    setWindowFlags( Qt::Window | Qt::FramelessWindowHint);
    resize(WIDTH, HEIGHT);

    camera.initialize(WIDTH, HEIGHT);
    controller.initialize(&camera);
}

void CameraScreen::paintEvent(QPaintEvent *)
{
    label->setPixmap(newFrame());
    controller.controlLoop();
}

QPixmap CameraScreen::newFrame()
{
    QPixmap p = QPixmap();
    camera.captureImage();
    p.loadFromData((const uchar *)camera.buffer, camera.bufferLen, 0, Qt::AutoColor);
    return p;
}
