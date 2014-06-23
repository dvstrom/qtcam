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
    void ParseProcess(QString strline);
    void HandleError(int errnum);
signals:

public slots:

private:
    bool abort;
    QString removeInvalid(QString line);
    bool G00Parse(QString strline);
    bool testRegexMatchx(QString testStr);
    bool testRegexMatchy(QString testStr);
    int  lcount(QString testStr);

};

#endif // GCODEPARSE_H
