#include "ballswindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BallsWindow w;
    w.show();

    return a.exec();
}
