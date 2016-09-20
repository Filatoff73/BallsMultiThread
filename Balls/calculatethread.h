#ifndef CALCULATETHREAD_H
#define CALCULATETHREAD_H
#include <QThread>
#include <QGraphicsItem>
#include "ball.h"
#include <QMutex>
#include <QMap>

class CalculateThread : public QThread
{
    Q_OBJECT

public:
    CalculateThread(QObject *parent=0);

    void run();

    void appentItem(QGraphicsItem* a);
    void removeItem(QGraphicsItem* a);


    bool getStopCalculate() const;
    void setStopCalculate(bool value);

private slots:
    void sl_updateBallPosition(const QPointF &newPos);

signals:
    void sg_finishCalculate(Ball* a, const QPointF& point);
private:
    QMap<Ball*,QPointF> _itemsListMap;
    bool stopCalculate;
    QMutex mutex;
};



#endif // CALCULATETHREAD_H
