#include "hole.h"
#include <QPainter>
#include <QtDebug>
#include <QGraphicsSceneMouseEvent>





double Hole::gethx()
{
    return hx;
}

double Hole::gethy()
{
    return hy;
}

double Hole::gethradius()
{
    return hradius;
}

QRectF Hole::boundingRect() const
{

    qreal penWidth=1;
    return QRectF(hx-hradius-penWidth, hy-hradius-penWidth, 2*hradius+penWidth, 2*hradius+penWidth);
}

void Hole::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::NoPen);
    painter->setBrush(hcolor);
    painter->drawEllipse(hx-hradius-1,hy-hradius-1,2*hradius,2*hradius);
    painter->setPen(Qt::white);
   // painter->drawLine((hx-hradius)-1,hy,(hx+hradius),hy);
    if(this->isSelected())
    {
        hcolor=Qt::green;
        painter->setBrush(hcolor);
    }
}

Hole::Hole(double x, double y, double radius)
  : QObject(),QGraphicsItem()
{
    hx=x;
    hy=y;
    hradius=radius;
    hcolor=Qt::red;
    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptsHoverEvents(true);

}
void Hole::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() ==Qt::LeftButton)
    {
//        if (QGraphicsItem *item = itemAt(event->pos())) {
//        Hole *holetemp1=qgraphicsitem_cast<Hole*>(item);
//             qDebug() << "You clicked on item" << item;
        qDebug()<<" the item has respond";
             qDebug()<<"You clicked on hole x:"<<this->gethx();
              qDebug()<<"You clicked on hole y:"<<this->gethy();

              //emit itemselected(this);
         } else {
             qDebug() << "You didn't click on an item.";
         }
     this->setSelected(true);
     update();
   //  QGraphicsItem::mousePressEvent(event);
    }


