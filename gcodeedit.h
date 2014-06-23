#ifndef GCODEEDIT_H
#define GCODEEDIT_H

#include <QPlainTextEdit>
#include <QVector>
#include "message.h"
#include "gcodeparse.h"
class GcodeParse;
class GcodeEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit GcodeEdit(QWidget *parent = 0);
  //  ~GcodeEdit();

    void highlightCurrentLine();
    void gotoline(int line);
    QVector<message> Arraymessage;
signals:

public slots:
    void compilegcode();
private:
    GcodeParse *wordparse;

};

#endif // GCODEEDIT_H
