#include "message.h"
#include <QIODevice>
#include <QDataStream>


//message::message(QObject *parent) :
//    QObject(parent)
//  {

//}

message::message(quint8 command, QByteArray commarray, quint16 commcrc)
      :messagearray()
{
    quint8 head=messagehead;
   // messagearray=new QByteArray();
    QDataStream messagestream(&messagearray,QIODevice::WriteOnly);

    messagestream<<head;
    messagestream<<command;
    quint8 length=commarray.size();
    messagestream<<length;
    //messagearray.append(commarray);
    //messagestream<<commarray;
    commcrc=0;
    messagestream<<commcrc;

    messagearray.insert(3,commarray);

}




