#ifndef GCODEPARSE_H
#define GCODEPARSE_H

#include <QObject>
#include "gcodeedit.h"
#include "message.h"
#include <QString>
class GcodeParse : public QObject
{
    Q_OBJECT
public:
    explicit GcodeParse(QObject *parent = 0);
 //   QVector<message> ParseProcess(QString strline);
    bool ParseProcess(QString strline,QVector<message>& mesvec);

    void HandleError(int errnum);
signals:

public slots:

private:
    bool abort;
    QString removeInvalid(QString line);
//    message* G00Parse(QString strline);
    bool G00Parse(QString strline,message &tempmsg);
    bool testRegexMatchx(QString testStr);
    bool testRegexMatchy(QString testStr);
    int  lcount(QString testStr);

};

#endif // GCODEPARSE_H
