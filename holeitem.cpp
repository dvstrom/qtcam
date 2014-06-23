#include "holeitem.h"
#include <QGraphicsItem>
//HoleItem::HoleItem(QObject *parent) :
//    QGraphicsItem(parent)
//{
//}

HoleItem::HoleItem(double hx, double hy, double radius){

}

QRectF HoleItem::boundingRect() const
{

}

double HoleItem::getradius()
{
    return this->radius;
}

double HoleItem::gethx()
{
    return this->hx;
}

double HoleItem::gethy()
{
    return this->hy;
}



