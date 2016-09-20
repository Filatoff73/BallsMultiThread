#include "ballswindow.h"
#include "ui_ballswindow.h"
#include <QScrollBar>
#include <QDebug>

BallsWindow::BallsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BallsWindow)
{
    ui->setupUi(this);
    scene = new Scene;
    view = new View;
    view->setScene(scene);
    ui->layout_view->addWidget(view);
    this->setGeometry(50,50,900,700);
    connect(ui->playButton,SIGNAL(clicked(bool)),scene,SLOT(sl_startStopPlaying()));

}

BallsWindow::~BallsWindow()
{
    qDebug()<<"destr";
    delete scene;
    delete view;
    delete ui;
}




