#include "mainwindow.h"
#include <QApplication>
#include <QSplitter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTextEdit>
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
