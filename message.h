#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>

#define backorigin 0x11
#define movex   0x22
#define messagehead 0xa5
#define movey 0x33
#define movexy 0x44
#define control 0x55
#define readstatus 0x66
#define  livescan 0x99

//typedef quint8 commands;
class message
{
   // Q_OBJECT
public:
   // explicit message(QObject *parent = 0);
    message();
    message(quint8 command1, QByteArray commarray1, quint16 commcrc);
    QByteArray messagearray;
    QByteArray commarray;
    //quint8 messagehead;
    quint8 command;
    quint8 datalength;
    quint32 commdata;
//    quint32 commdatax;
//    quint32 commdatay;
//    quint8 commcontrol1;
//    quint8 commcontrol2;
//    quint8 commread;
//    quint16 commcrc;

    quint8 messagelenth;
    quint8 messagetype;



signals:

public slots:

};


#endif // MESSAGE_H
