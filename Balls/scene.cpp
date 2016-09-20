#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "qmath.h"
#include <QDebug>
#include <QGraphicsView>
#include <QPushButton>


Scene::Scene(QGraphicsScene *parent) : QGraphicsScene(parent)
{
    this->setSceneRect(0,0,SCENCE_SIZE_X,SCENCE_SIZE_Y);
    this->addItem(new Ball);
    calcThread = new CalculateThread();
    this->items(Qt::AscendingOrder).last()->setPos(120,120);
    foreach (QGraphicsItem* ball, items(Qt::AscendingOrder))
    {
        calcThread->appentItem(ball);
    }
    isPlaying=false;

    connect(calcThread,SIGNAL(sg_finishCalculate(Ball*,QPointF)),this,SLOT(sl_setPosItem(Ball*,QPointF)));
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button()==Qt::RightButton)
    {
        QList<QGraphicsItem*> l = items(mouseEvent->scenePos());
        if(l.size()<=0)
        {
            this->addItem(new Ball);
            this->items(Qt::AscendingOrder).last()->setPos(mouseEvent->scenePos());
            calcThread->appentItem(this->items(Qt::AscendingOrder).last());
        }
        else
        {
            Ball* temp = dynamic_cast<Ball*>(l.at(0));
            calcThread->removeItem(temp);
            removeItem(temp);

        }

    }

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void Scene::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    const int gridSize = GREED_SIZE;

    const int realLeft = 0;
    const int realRight = SCENCE_SIZE_X;
    const int realTop = 0;
    const int realBottom = SCENCE_SIZE_Y;

    // Draw grid.
    const int firstLeftGridLine = realLeft - (realLeft % gridSize);
    const int firstTopGridLine = realTop - (realTop % gridSize);

    QVarLengthArray<QLine, 100> lines;

    for (qreal x = firstLeftGridLine; x <= realRight; x += gridSize)
        lines.append(QLine(x, realTop, x, realBottom));
    for (qreal y = firstTopGridLine; y <= realBottom; y += gridSize)
        lines.append(QLine(realLeft, y, realRight, y));

    //painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(QColor(220, 220, 220), 0.0));
    painter->drawLines(lines.data(), lines.size());

    // Draw axes.
    painter->setPen(QPen(Qt::lightGray, 0.0));
    painter->drawLine(0, realTop, 0, realBottom);
    painter->drawLine(realLeft, 0, realRight, 0);

    painter->setPen(QPen(Qt::red, 0.0));
    painter->drawLine(0, 0, 0, SCENCE_SIZE_Y);
    painter->drawLine(0, SCENCE_SIZE_Y, SCENCE_SIZE_X, SCENCE_SIZE_Y);
    painter->drawLine(SCENCE_SIZE_X, SCENCE_SIZE_Y, SCENCE_SIZE_X, 0);
    painter->drawLine(SCENCE_SIZE_X, 0, 0, 0);

}

Scene::~Scene()
{
    qDebug()<<"destr_scene";
    calcThread->setStopCalculate(true);
    while(!calcThread->wait())
        qDebug()<<"waiting thread exit";
    delete calcThread;
}

void Scene::sl_startStopPlaying()
{
    isPlaying=!isPlaying;
    if(isPlaying)
    {
        calcThread->setStopCalculate(false);
        dynamic_cast<QPushButton*>(sender())->setText("Pause");
        calcThread->start();

    }
    else
    {
        calcThread->setStopCalculate(true);
        dynamic_cast<QPushButton*>(sender())->setText("Play");
    }
}

void Scene::sl_setPosItem(Ball *a, const QPointF &point)
{
    a->setPos(point);
}

