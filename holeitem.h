#ifndef HOLEITEM_H
#define HOLEITEM_H

#include <QGraphicsItem>

class HoleItem : public QGraphicsItem
{
    Q_OBJECT
public:
    explicit HoleItem(QObject *parent = 0);
    double radius;
    double hx;
    double hy;
    HoleItem(double hx,double hy,double radius);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    double getradius();
    double gethx();
    double gethy();
signals:

public slots:

};

#endif // HOLEITEM_H
