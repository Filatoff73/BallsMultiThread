#include "calculatethread.h"
#include "qmath.h"
#include <QDebug>
#include "consts.h"
#include <QTime>




CalculateThread::CalculateThread(QObject* parent) : QThread(parent)
{
    stopCalculate=true;
}

void CalculateThread::run()
{
    int cycle=0;
    QTime time;

    while(!stopCalculate)
    {
        if(cycle==0)
            time.start();
        mutex.lock();
        QList<Ball*> list = _itemsListMap.keys();

        foreach (Ball* ball, list)
        {
            QPointF curPosition = _itemsListMap.value(ball);
            if(ball->isMoving())
                continue;
            double forceX;
            double forceY;
            double forceXY;
            double sinus;
            double cosinus;
            double realForce;
            QPointF newPos=curPosition;
            double dx = 0.0;
            double dy = 0.0;
            foreach(Ball* ball2, list)
            {
                if(ball2==ball || ball2->isMoving())
                    continue;
                forceX=_itemsListMap.value(ball2).x()-curPosition.x();
                forceY=_itemsListMap.value(ball2).y()-curPosition.y();
                forceXY = sqrt(pow(forceX,2)+pow(forceY,2));
                if(forceXY>1)
                {
                    sinus = forceY/forceXY;
                    cosinus = forceX/forceXY;
                    realForce = 1.0/forceXY - 1/(pow(forceXY,2));
                    dx += realForce*cosinus*FORCE_KOEF;
                    dy += realForce*sinus*FORCE_KOEF;
                }
            }
            newPos.setX(curPosition.x()+dx);
            newPos.setY(curPosition.y()+dy);

            emit sg_finishCalculate(ball,newPos);
            _itemsListMap.insert(ball,newPos);
        }
        mutex.unlock();
        cycle++;
        if(cycle == CYCLES_COUNT_SLEEP)
        {
            cycle=0;
            int msec =time.elapsed();
            if(msec<CYCLES_TIME_SLEEP)
            {
                msleep(CYCLES_TIME_SLEEP-msec);
            }
        }

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


