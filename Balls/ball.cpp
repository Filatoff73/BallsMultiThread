#include "ball.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QApplication>
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

Ball::Ball(QGraphicsObject *parent) : QGraphicsObject(parent)
{
    setAcceptDrops(true);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    _isMoving=false;
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawEllipse(0,0,RAD_BALL,RAD_BALL);
}



QRectF Ball::boundingRect() const
{
    return QRectF(0,0,RAD_BALL,RAD_BALL);
}

void Ball::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button()==Qt::LeftButton)
    {
        _isMoving=true;
    }
    QGraphicsObject::mousePressEvent(mouseEvent);
}

void Ball::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button()==Qt::LeftButton)
    {
        _isMoving=false;
        emit sg_positionChange(this->pos());
    }
    QGraphicsObject::mouseReleaseEvent(mouseEvent);
}

QVariant Ball::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene())
    {
        QPointF newPos = value.toPointF();

        if(newPos.x()<0)
        {
            newPos.setX(0);
        }

        if(newPos.y()<0)
        {
            newPos.setY(0);
        }

        if(newPos.x()>SCENCE_SIZE_X-RAD_BALL)
            newPos.setX(SCENCE_SIZE_X-RAD_BALL);

        if(newPos.y()>SCENCE_SIZE_Y-RAD_BALL)
            newPos.setY(SCENCE_SIZE_Y-RAD_BALL);

        return newPos;
    }
    else
        return QGraphicsItem::itemChange(change, value);
}

bool Ball::isMoving() const
{
    return _isMoving;
}

void Ball::setIsMoving(bool isMoving)
{
    _isMoving = isMoving;
}

