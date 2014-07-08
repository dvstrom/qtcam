#include "message.h"
#include <QIODevice>
#include <QDataStream>


//message::message(QObject *parent) :
//    QObject(parent)
//  {

//}

message::message()
{

}

message::message(quint8 command1, QByteArray commarray1, quint16 commcrc)
      :messagearray()
{
    this->command=command1;
    this->commarray=commarray1;
    this->datalength=this->commarray.size();
    quint8 head=messagehead;
   // messagearray=new QByteArray();
    QDataStream messagestream(&messagearray,QIODevice::WriteOnly);

    messagestream<<head;
    messagestream<<this->command;
    //quint8 length=commarray.size();
    //messagestream<<length;
    messagearray.append(this->commarray);
    //messagestream<<commarray;
    commcrc=0;

    messagearray.append(commcrc);

   // messagearray.insert(3,commarray);
   this->messagelenth=messagearray.size();
}




