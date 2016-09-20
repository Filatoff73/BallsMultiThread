#include "calculatethread.h"
#include "qmath.h"
#include <QDebug>
#include "consts.h"




CalculateThread::CalculateThread(QObject* parent) : QThread(parent)
{
    stopCalculate=true;
}

void CalculateThread::run()
{

    while(!stopCalculate)
    {
        mutex.lock();
        QList<Ball*> list = _itemsListMap.keys();
        foreach (Ball* ball, list)
        {
            QPointF curPosition = _itemsListMap.value(ball);
            if(ball->isMoving())
                continue;
            double forceX = 0.0;
            double forceY = 0.0;
            double forceXY = 0.0;
            double sinus;
            double cosinus;
            double realForce;
            QPointF newPos=curPosition;
            foreach(Ball* ball2, list)
            {
                if(ball2==ball || ball2->isMoving())
                    continue;
                forceX+=_itemsListMap.value(ball2).x()-curPosition.x();
                forceY+=_itemsListMap.value(ball2).y()-curPosition.y();
            }
            forceXY = sqrt(pow(forceX,2)+pow(forceY,2));
            sinus = forceY/forceXY;
            cosinus = forceX/forceXY;
            if(forceXY>1)
            {
                realForce = 1.0/forceXY - 1/(pow(forceXY,2));
                double dx = realForce*cosinus;
                double dy = realForce*sinus;
                dx=dx*FORCE_KOEF;
                dy=dy*FORCE_KOEF;
                newPos.setX(curPosition.x()+dx);
                newPos.setY(curPosition.y()+dy);

            }

            emit sg_finishCalculate(ball,newPos);
            _itemsListMap.insert(ball,newPos);
        }
        mutex.unlock();
    }


}

void CalculateThread::appentItem(QGraphicsItem *a)
{    
    mutex.lock();
    Ball* ball = dynamic_cast<Ball*>(a);
    _itemsListMap.insert(ball,ball->pos());
    mutex.unlock();
    connect(ball,SIGNAL(sg_positionChange(QPointF)),this,SLOT(sl_updateBallPosition(QPointF)));
}

void CalculateThread::removeItem(QGraphicsItem *a)
{
    mutex.lock();
    Ball* ball = dynamic_cast<Ball*>(a);
    if(_itemsListMap.contains(ball))
    {
        disconnect(ball,0,this,0);
        _itemsListMap.remove(ball);
    }
    mutex.unlock();
}

bool CalculateThread::getStopCalculate() const
{
    return stopCalculate;
}

void CalculateThread::setStopCalculate(bool value)
{
    stopCalculate = value;
}

void CalculateThread::sl_updateBallPosition(const QPointF& newPos)
{
    Ball* ball = dynamic_cast<Ball*>(sender());
    mutex.lock();
    if(_itemsListMap.contains(ball))
        _itemsListMap.insert(ball,newPos);
    mutex.unlock();
}


