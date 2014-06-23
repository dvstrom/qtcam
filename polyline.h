#ifndef POLYLINE_H
#define POLYLINE_H

#include <QObject>

class PolyLine : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit PolyLine(QObject *parent = 0);

signals:

public slots:

};

#endif // POLYLINE_H
