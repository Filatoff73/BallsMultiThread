#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include "ball.h"
#include "consts.h"
#include "calculatethread.h"
#include <QMutex>


class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(QGraphicsScene* parent = 0);

    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);

    void drawBackground(QPainter *painter, const QRectF &rect);

    ~Scene();

public slots:
    void sl_startStopPlaying();
    void sl_setPosItem(Ball* a, const QPointF& point);

private:
    CalculateThread* calcThread;
    bool isPlaying;

};

#endif // SCENE_H
