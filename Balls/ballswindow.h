#ifndef BALLSWINDOW_H
#define BALLSWINDOW_H

#include <QMainWindow>
#include "scene.h"
#include "view.h"
#include "calculatethread.h"


namespace Ui {
class BallsWindow;
}

class BallsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BallsWindow(QWidget *parent = 0);
    ~BallsWindow();

private:
    Ui::BallsWindow *ui;
    View* view;
    Scene* scene;

};

#endif // BALLSWINDOW_H
