#include "CameraScreen.h"
#include <time.h> 

CameraScreen::CameraScreen(QWidget *parent) : QWidget(parent)
{
    label = new QLabel("camera frame", this);
    label->setGeometry(0, 0, STREAM_WIDTH, STREAM_HEIGHT);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&CameraScreen::update));
    timer->start((int)(1000/FRAMES_PER_SEC));

    setWindowFlags( Qt::Window | Qt::FramelessWindowHint);
    resize(STREAM_WIDTH, STREAM_HEIGHT);

    controller.initialize(&camera);
}

void CameraScreen::paintEvent(QPaintEvent *)
{
    controller.controlLoop(); //Should be the first command, can cause trouble if not.
    label->setPixmap(newFrame());
}

QPixmap CameraScreen::newFrame()
{
    QPixmap p = QPixmap();
    camera.streamFrame();
    p.loadFromData((const uchar *)camera.buffer, camera.bufferLen, 0, Qt::AutoColor);
    return p;
}
