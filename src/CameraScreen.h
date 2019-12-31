#ifndef _CAMERASCREEN_H_
#define _CAMERASCREEN_H_

#include <QLabel>
#include <QImage>
#include <QWidget>
#include <QTime>
#include <QTimer>

class CameraScreen : public QWidget
{
    Q_OBJECT

public:
    CameraScreen(QWidget *parent = nullptr);
    void setDimensions(int w, int h);
    void newFrame(void* buffer, int bufferLen);
protected:
    QLabel* label;
    int newHeight, newWidth;
};

#endif
