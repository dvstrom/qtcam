#include "gcodeparse.h"
#include <qdebug.h>
#include "message.h"
GcodeParse::GcodeParse(QObject *parent) :
    QObject(parent)
{
    abort=false;
}


//QVector<message> GcodeParse::ParseProcess(QString strline)
bool GcodeParse::ParseProcess(QString strline,QVector<message>& mesvec)

{
//    char buf[20];
//    while((strline!=NULL)&&(!abort))
//    {
//        for(int i=0;i<20;i++)
//            buf[i]=0;
//        strline = strline.trimmed();
//        if((strline.at(0)=='(')||(strline.at(0)=='%'))
//        {}//ignore comments
//        else
//        {
//            strline = strline.toUpper();
//            int times = strline.count("G");
//            if (times>1)
//            {
//                strline = removeInvalid(strline);
//            }

//        }
//}
   //  QVector<message> Arraycommmessage;
    int lnum=1;//记录语句中循环的次数
    //message* commsg;
    message  commsg;
     qDebug()<<"this is in functuin GcodeParse::ParseProcess() begin";
     bool parseback;
     if ((strline!=NULL)&&(!abort))
     {

         qDebug()<<strline;
         strline = strline.trimmed();//去掉两端多余空格
         if((strline.at(0)=='(')||(strline.at(0)=='%'))
              {}//忽略注释
         else
         {
             strline = strline.toUpper();//转为大写
          }
         if(strline.contains("L",Qt::CaseInsensitive)) //查是否包含q，大小写不敏感
         {
             qDebug()<<"this is the L sentence";
             lnum=lcount(strline);
         }

         if(strline.contains("G00",Qt::CaseInsensitive)) //查是否包含q，大小写不敏感
         {
             qDebug()<<"this is the G00 sentence";
             commsg=message();
              parseback=G00Parse(strline,commsg);

             //commsg=G00Parse(strline);

         }
         else if(strline.contains("G20",Qt::CaseInsensitive))
         {
                qDebug()<<"this is the g20 sentence";
         }
         else if(strline.contains("M",Qt::CaseInsensitive))
         {
                qDebug()<<"this is the M sentence";
         }
         else
         {
             //读入不合法的语句
             HandleError(1);
         }
     }
     else
       {
           //当读入的行为空时报错
       }
     qDebug()<<strline;
     for(int i=0;i<lnum;i++)
     {
         mesvec.append(commsg);
     }
     qDebug()<<"this is in functuin GcodeParse::ParseProcess() end";
  //   return Arraycommmessage;
     return  true;

}

void GcodeParse::HandleError(int errnum)
{
    QString errinfo;
    switch(errnum)
    {
        case 1:
            errinfo="输入语句不合法！";
            break;
        case 2:
            errinfo="非法程序段开始！";
            break;
        case 3:
             errinfo="非法程序语句！";
             break;
         case 4:
              errinfo="缺少参数！";
              break;
    default:
           break;


    }

}


//没用
QString GcodeParse::removeInvalid(QString line)
    {
        QStringList components = line.split(" ",QString::SkipEmptyParts);
        line="";
        QString s;
        foreach(s,components)
        {
            int value = s.mid(1,-1).toInt();
            if(value>4&&value<17)
            {}
            else if(value>21&&value<28)
            {}
            else if(value>28&&value<53)
            {}
            else if(value>53&&value<80)
            {}
            else if(value>80&&value<90)
            {}
            else if(value>94)
            {}
            else
                line.append(s).append(" ");
        }
        return line.trimmed();
}

//message* GcodeParse::G00Parse(QString  parsestr)
bool GcodeParse::G00Parse(QString  parsestr,message &tempmsg)
{
//    if (strline.mid(0,3)!="G00")
//    {
//        HandleError(2);
//        return 1;
//     }
//    else
//     {
//        if(strline.contains("X",Qt::CaseInsensitive))
//     }
    qDebug()<<"this is the function G00Parse begin";
    int tempx=0;
    int tempy=0;
    quint8  tempcom;
    message* msg;
    parsestr.simplified();//替换内部多个空白
    bool parsex;
    bool parsey;
    QStringList components = parsestr.split(" ",QString::SkipEmptyParts);//分解为子串

    QString s;
    if(components.size()>4)
    {
        HandleError(3);
    }
    foreach(s,components)
    {
         qDebug()<<s;
    }

    if(components.at(0)!="G00")
    {
        HandleError(2);
        return false;

    }


        QString patternx=("\\bX+\\S+\\b");

        //  \b开始字符和结束字符  \w 任意字符
        QRegExp rx(patternx);
        int positx=components.indexOf(rx);
        if(positx != -1)
        {
         parsex=1;
        QString xnum=components.at(positx);
         qDebug()<<xnum;
         qDebug()<<xnum.mid(1);
         tempx=xnum.mid(1).toInt();
         qDebug()<<tempx;
        }
        else
        {
            parsex=0;
        }

        QString patterny=("\\bY+\\S+\\b");
        QRegExp ry(patterny);
        int posity=components.indexOf(ry);
        if(posity != -1)
        {
            parsey=1;
        QString ynum=components.at(posity);
         qDebug()<<ynum;
         tempy=ynum.mid(1).toInt();
         qDebug()<<ynum.mid(1);
         qDebug()<<tempy;
       }
        else
        {
            parsey=0;
        }

        if(parsex&&parsey)
        {
             qDebug()<<"the sentence have x and y";
             tempcom=movexy;
             QByteArray commandarr1;
             QDataStream comm(&commandarr1,QIODevice::WriteOnly);
              comm<<tempx;
              comm<<tempy;
              quint16  messagecrc=0;//crc暂时为0
              msg=new message(tempcom,commandarr1,messagecrc);
        }
        else  if(parsex)
            {
                qDebug()<<"the sentence have x ";
                tempcom=movex;
                QByteArray commandarr1;
                QDataStream comm(&commandarr1,QIODevice::WriteOnly);
                 comm<<tempx;
                 quint16  messagecrc=0;//crc暂时为0
                msg=new message(tempcom,commandarr1,messagecrc);
            }
        else if(parsey)
            {
                qDebug()<<"the sentence have  y";
                tempcom=movey;
                QByteArray commandarr1;
                QDataStream comm(&commandarr1,QIODevice::WriteOnly);
                 comm<<tempy;
                 quint16  messagecrc=0;//crc暂时为0
                 msg=new message(tempcom,commandarr1,messagecrc);
            }
         else
            {
               qDebug()<<"the sentence wrong";
                HandleError(4);
                return false;
            }

    qDebug()<<"this is the function G00Parse end";
    tempmsg=*msg;
    return true;
}
//没用
bool GcodeParse::testRegexMatchx(QString testStr)
{
     QString patternx=("\\bX+\\d+\\b");
     QRegExp rx(patternx);
     bool match=rx.exactMatch(testStr);
     return match;    //命中返回true

}
//没用
bool GcodeParse::testRegexMatchy(QString testStr)
{
    QString patterny=("\\bY+\\d+\\b");
    QRegExp ry(patterny);
    bool match=ry.exactMatch(testStr);
    return match;    //命中返回true
}
//得到语句中循环的次数
int GcodeParse::lcount(QString testStr)
{
    QString patterl=("\\bL+\\d+\\b");
    QRegExp rl(patterl);
    int pos=rl.indexIn(testStr);
    QString result;
   if(pos!=-1)
  {
//       qDebug()<<rl.matchedLength();
//        qDebug()<<rl.cap(0);
        result=rl.cap(0);
   }
   int lcount=result.mid(1).toInt();
  qDebug()<<"this is the code cycles:"<<lcount;
   return lcount;
}
