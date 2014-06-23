#ifndef HOLE_H
#define HOLE_H

#include <QGraphicsItem>
#include "itemtypes.h"
#include <QMouseEvent>

class Hole :public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
   // Hole(QGraphicsItem * parent = 0);
    enum {Type = HoleType};
    double gethx();
    double gethy();
    double gethradius();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                      QWidget *widget);
    Hole(double x,double y,double radius);
    double hx;
    double hy;
    double hradius;
    QColor  hcolor;
    int type() const { return Type; }

private:

public slots:
signals:
    void itemselected(Hole  *hole);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};


#endif // HOLE_H
