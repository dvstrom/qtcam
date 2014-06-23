#include "dxfview.h"
 #include <QtGui>
#include <hole.h>



void DxfView::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
void DxfView::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void DxfView::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        event->ignore();
        if (QGraphicsItem *item = itemAt(event->pos())) {
        Hole *holetemp1=qgraphicsitem_cast<Hole*>(item);
             qDebug() << "You clicked on view item:" << item;
             qDebug()<<"You clicked on hole x:"<<holetemp1->gethx();
              qDebug()<<"You clicked on hole y:"<<holetemp1->gethy();
            emit itemselected(holetemp1);

         } else {
             qDebug() << "You didn't click on an item.";
         }
        qDebug()<<"view clicked";
        QGraphicsView::mousePressEvent(event);
    }
}
