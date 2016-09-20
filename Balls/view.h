#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
class View : public QGraphicsView
{
public:
    View(QGraphicsView* parent=0);
    ~View();
};

#endif // VIEW_H
