#ifndef BALL_H
#define BALL_H

#include <QGraphicsObject>


#include "consts.h"

class Ball : public QGraphicsObject
{
    Q_OBJECT

public:
    Ball(QGraphicsObject* parent=0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF boundingRect() const ;

    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    bool isMoving() const;
    void setIsMoving(bool isMoving);

private:
    bool _isMoving;

signals:
    void sg_positionChange(const QPointF& newPos);
};

#endif // BALL_H
