#include <QLabel>
#include <QImage>
#include <QWidget>
#include <QTime>
#include <QTimer>
#include "CameraSensor.h"
#include "CameraControl.h"

#define FRAMES_PER_SEC 60
#define WIDTH 640
#define HEIGHT 480 

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
