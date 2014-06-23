#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "hole.h"
#include <QMainWindow>
#include <QSplitter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTextEdit>
#include <QString>
#include <QPushButton>
#include "dxfview.h"
#include "posix_qextserialport.h"
#include <qmath.h>
#include <QPlainTextEdit>
#include <QSlider>
#include "message.h"
#include <QGroupBox>
#include <QRadioButton>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolButton>
#include <configdialog.h>
#include "gcodeedit.h"
//class QAction;
//class QMenu;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    message generatemessage(Hole* hole1,Hole* hole2);
    QVector<Hole*> holeVec;
 private:
    void createActions();
    void createMenus();
    void creatviewandscene();
    void creatbuttons();
    void creatsplitter();
    void creatconnect();
    QMenu *fileMenu;
    QMenu *optionsMenu;
    QMenu *helpMenu;
    QAction *openSettingsAct;
    QAction *openIniFileAct;
    QAction *openPropertyListAct;
    QAction *openRegistryPathAct;
    QAction *refreshAct;
    QAction *exitAct;
    QAction *autoRefreshAct;
    QAction *configAct;
    QAction *fallbacksAct;
    QAction *aboutAct;
    QAction *aboutQtAct;


    QSplitter *splitterMain;
    QGraphicsScene *dxfscene;
    DxfView *dxfview;
    QSplitter *splitterRight;
    GcodeEdit  *textTop;
    //GcodeEdit *gcodeedit;
    QPlainTextEdit *textBottom;
    QPushButton *load;
    QPushButton *count;
    QPushButton *simulation;
    QPushButton *send;
    QPushButton *finish;
    QPushButton *compiler;
    QPushButton *display;
    QGroupBox *selectGroup;
    QRadioButton *zhengjiaoType;
    QRadioButton *zuijinType ;
    QRadioButton *zidingyiType ;
    QToolButton *zoomInIcon;
    QToolButton *zoomOutIcon;
    QWidget *zoomwidget;
    QTimer *time ;
    //commThread *commthread;

    Posix_QextSerialPort *hcomm;
   QSlider *zoomSlider;
  //  void gotoline(int line);

  //  void highlightCurrentLine();
    void  zhengjiaosort( );
    void nearpointpath();
    void generategcode();
    message generatemessage(Hole hole1,Hole hole2);
    // void connectItem(QGraphicsItem *item);//链接item与窗口信号
    bool eventFilter(QObject *target, QEvent *event);
public slots:
    void openfile();
    void countholl();
    void wirtecomm();
    void readcomm();
    void closeThread();
    //    void displaycomm();
    void simulater();
   void zoomIn();
    void zoomOut();
    void setupMatrix();
    void loadFile();
    void selectitem(Hole *hole);

    void configsetting();


 public:
    QString path;
  //  QVector<QString> gcodeVec;
    ConfigDialog *configdialog;
};


//class CompLessX
// {
// public:
//     bool operator ()(const Hole* pstItem1, const Hole* pstItem2)
//     {
//         return pstItem1->hx < pstItem2->hx;
//     }
// };


//class CompGreaterX
// {
// public:
//     bool operator ()(const Hole* pstItem1, const Hole* pstItem2)
//     {
//         return pstItem1->hx > pstItem2->hx;
//     }
// };

//class CompLessY
// {
// public:
//     bool operator ()(const Hole* pstItem1, const Hole* pstItem2)
//     {
//         return pstItem1->hy < pstItem2->hy;
//     }
// };


//class CompGreaterY
// {
// public:
//     bool operator ()(const Hole* pstItem1, const Hole* pstItem2)
//     {
//         return pstItem1->hy > pstItem2->hy;
//     }
// };
//class CompGreaterYX
// {
// public:
//     bool operator ()(const Hole* pstItem1, const Hole* pstItem2)
//     {
//         if (pstItem1->hy < pstItem2->hy)
//         {
//             return true;
//         }
//         else
//         {
//             if (pstItem1->hy== pstItem2->hy)
//             {
//                 return pstItem1->hx < pstItem2->hx;
//             }
//             else
//             {
//                 return false;
//             }
//         }


//     }
// };
//class CompTwoHole
// {
//private:
//    Hole* firstItem;
// public:
//    CompTwoHole(Hole* hole):firstItem(hole){};
//     bool operator ()(const Hole* pstItem1, const Hole* pstItem2)
//     {
//         return sqrt((pow((pstItem1->hx-firstItem->hx),2)
//                      +pow((pstItem1->hy-firstItem->hy),2)))<
//                 sqrt((pow((pstItem2->hx-firstItem->hx),2)
//                       +pow((pstItem2->hy-firstItem->hy),2)));
//     }
// };

#endif // MAINWINDOW_H
