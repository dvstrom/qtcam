#include "gcodeedit.h"
#include <QTextBlock>
#include <QTextCursor>
#include <qdebug.h>
GcodeEdit::GcodeEdit(QWidget *parent) :
    QPlainTextEdit(parent)
{
    this->wordparse=new GcodeParse;
}

void GcodeEdit::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections=this->extraSelections();

    if (!this->isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::blue).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = this->textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    this->setExtraSelections(extraSelections);
}

void GcodeEdit::gotoline(int line)
{
   // QTextCursor tc = this->textCursor();
    QTextBlock tb=this->document()->findBlockByNumber(line-1);
    qDebug()<<tb.text();
    qDebug()<<"-------------------------------------------------------------------";
    int  position  = tb.position();
    QTextCursor tc(tb);
    //tc.setPosition(0);
     tc.setPosition(position,QTextCursor::MoveAnchor);
     tc.select(QTextCursor::BlockUnderCursor);//选中整行
     this->setTextCursor(tc);
}

void GcodeEdit::compilegcode()
{
    qDebug()<<"this is in functuin GcodeEdit::compilegcode() begin";
    int blocknum=0;
    bool compileok;
    while(blocknum<this->document()->blockCount())
    {
        qDebug()<<blocknum;
        QVector<message> messagecomm;
        qDebug()<<this->document()->findBlockByNumber(blocknum).text();
        compileok=wordparse->ParseProcess(this->document()->findBlockByNumber(blocknum).text(),
                                          messagecomm);
        Arraymessage+=messagecomm;
        blocknum++;
    }
    qDebug()<<"this is in functuin GcodeEdit::compilegcode() end";
    message msg;
    foreach (msg, Arraymessage) {


    }
}
