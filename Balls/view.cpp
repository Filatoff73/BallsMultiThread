#include "view.h"
#include <QScrollBar>
#include <QDebug>

View::View(QGraphicsView *parent) : QGraphicsView(parent)
{
    this->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    this->horizontalScrollBar()->setValue(1);
    this->verticalScrollBar()->setValue(1);

    this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
}

View::~View()
{
    qDebug()<<"destr_view";
}

