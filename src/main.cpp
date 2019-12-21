#include <QApplication>
#include "CameraScreen.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    CameraScreen screen; 
    screen.show();

    return app.exec();
}
