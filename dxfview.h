#ifndef DXFVIEW_H
#define DXFVIEW_H
#include <hole.h>
#include <QGraphicsView>

class DxfView : public QGraphicsView
{
       Q_OBJECT
public:
    explicit DxfView(QWidget *parent = 0): QGraphicsView(parent)
    {
        setDragMode(RubberBandDrag);
    }

public slots:
signals:
   void itemselected(Hole  *hole);
protected:
    void wheelEvent(QWheelEvent *event);
     void scaleView(qreal scaleFactor);
    void mousePressEvent(QMouseEvent *event);
};

#endif // DXFVIEW_H
