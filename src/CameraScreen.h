#ifndef _CAMERASCREEN_H_
#define _CAMERASCREEN_H_

#include <QLabel>
#include <QImage>
#include <QWidget>
#include <QTime>
#include <QTimer>
#include "CameraSensor.h"
#include "CameraControl.h"

class CameraScreen : public QWidget
{
    Q_OBJECT

public:
    CameraScreen(QWidget *parent = nullptr);

protected:
    QLabel* label;
    CameraSensor camera;
    CameraControl controller;
    void paintEvent(QPaintEvent *event) override;
    QPixmap newFrame();
};

#endif
