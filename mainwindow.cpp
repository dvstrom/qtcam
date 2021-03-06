#include "common.h"
#include "mainwindow.h"
#include <QSplitter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTextEdit>
#include <QPushButton>
#include "circleread.h"
#include <QFileDialog>
#include <QString>
#include <QPen>
#include <QMessageBox>
#include <QGraphicsLineItem>
#include "src/dl_dxf.h"
#include <QDebug>
#include <hole.h>
#include <algorithm>
 #include <functional>
#include <QString>
#include <QtDebug>
#include <QTimer>
#include <QElapsedTimer>
#include <QCoreApplication>
#include <QTextBlock>
#include <QTextCursor>
#include <QTextCodec>
#include <QToolButton>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QDataStream>
#include <QMenu>
#include <QMenuBar>
#include <QProcess>


//settingobject *setobj=new settingobject();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

       QTextCodec::setCodecForTr(QTextCodec::codecForName("gb18030"));
    this->resize(800,400);


        createActions();
        createMenus();
        creatviewandscene();
        creatbuttons();
        creatsplitter();





        //串口设置
//       commthread = new commThread;
//       commthread->start();          //启动线程
//       commthread->stopped=1;        //初始化变量
//       commthread->write_rs=0;
//       commthread->read_rs=0;
//       QTimer *time = new QTimer(this);   //新建定时类
//       time->start(50);                   //50ms定时

        hcomm=new Posix_QextSerialPort("/dev/ttyS0",QextSerialBase::Polling);
        hcomm->open(QIODevice::ReadWrite);
        hcomm->setBaudRate(BAUD9600);
        hcomm->setDataBits(DATA_8);

        hcomm->setParity(PAR_NONE);//校验位无
        hcomm->setStopBits(STOP_1);//1位停止位
        hcomm->setFlowControl(FLOW_OFF);//无数据流控制
        hcomm->setTimeout(10);//延时
        time = new QTimer(this);   //新建定时类
       time->start(50);                   //50ms定时
          creatconnect();



    }

    MainWindow::~MainWindow()
    {

    }
   void MainWindow::createActions()
   {

       openSettingsAct = new QAction(QString::fromLocal8Bit("设置"), this);
       //openSettingsAct->setShortcuts(QKeySequence::Open);
       //connect(openSettingsAct, SIGNAL(triggered()), this, SLOT(openSettings()));

       openIniFileAct = new QAction(QString::fromLocal8Bit("打开dxf文件"), this);
      // openIniFileAct->setShortcut(tr("Ctrl+N"));
       //connect(openIniFileAct, SIGNAL(triggered()), this, SLOT(openIniFile()));

       openPropertyListAct = new QAction(tr("Open Mac &Property List..."), this);
       openPropertyListAct->setShortcut(tr("Ctrl+P"));
       //connect(openPropertyListAct, SIGNAL(triggered()),
        //       this, SLOT(openPropertyList()));

       openRegistryPathAct = new QAction(tr("Open Windows &Registry Path..."),
                                         this);
       openRegistryPathAct->setShortcut(tr("Ctrl+G"));
//       connect(openRegistryPathAct, SIGNAL(triggered()),
//               this, SLOT(openRegistryPath()));

       refreshAct = new QAction(tr("&Refresh"), this);
       refreshAct->setShortcut(tr("Ctrl+R"));
       refreshAct->setEnabled(false);
       //connect(refreshAct, SIGNAL(triggered()), settingsTree, SLOT(refresh()));

       exitAct = new QAction(QString::fromLocal8Bit("退出"), this);
       exitAct->setShortcuts(QKeySequence::Quit);
       //connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

       autoRefreshAct = new QAction(tr("&Auto-Refresh"), this);
       autoRefreshAct->setShortcut(tr("Ctrl+A"));
       autoRefreshAct->setCheckable(true);
       autoRefreshAct->setEnabled(false);
//       connect(autoRefreshAct, SIGNAL(triggered(bool)),
//               settingsTree, SLOT(setAutoRefresh(bool)));
//       connect(autoRefreshAct, SIGNAL(triggered(bool)),
//               refreshAct, SLOT(setDisabled(bool)));

       configAct = new QAction(QString::fromLocal8Bit("设置"), this);
       configAct->setShortcut(tr("Ctrl+c"));
       configAct->setCheckable(true);
       configAct->setEnabled(true);
//       connect(autoRefreshAct, SIGNAL(triggered(bool)),
//               settingsTree, SLOT(setAutoRefresh(bool)));
//       connect(autoRefreshAct, SIGNAL(triggered(bool)),
//               refreshAct, SLOT(setDisabled(bool)));

       fallbacksAct = new QAction(tr("&Fallbacks"), this);
       fallbacksAct->setShortcut(tr("Ctrl+F"));
       fallbacksAct->setCheckable(true);
       fallbacksAct->setEnabled(false);
//       connect(fallbacksAct, SIGNAL(triggered(bool)),
//               settingsTree, SLOT(setFallbacksEnabled(bool)));

       aboutAct = new QAction(tr("&About"), this);
   //    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

       aboutQtAct = new QAction(tr("About &Qt"), this);
      // connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

   #ifndef Q_WS_MAC
       openPropertyListAct->setEnabled(false);
   #endif
   #ifndef Q_WS_WIN
       openRegistryPathAct->setEnabled(false);
   #endif
   }
   void MainWindow::creatviewandscene()
   {
       dxfscene=new QGraphicsScene(this);
      //dxfscene->addText("dxfscene");
      dxfscene->setBackgroundBrush(Qt::black);
      dxfview=new DxfView(this);
      dxfview->setFixedSize(600,300);
      dxfview->setScene(dxfscene);


     //     dxfview->installEventFilter(this);
      connect(dxfview,SIGNAL(itemselected(Hole*))
              ,this,SLOT(selectitem(Hole*)));

      //背景设置
   dxfview->setAutoFillBackground(true);
   QPalette p=dxfview->palette();
   p.setColor(QPalette::Window,Qt::red);
   QBrush brush;
   brush.setColor(Qt::white);
   brush.setStyle(Qt::DiagCrossPattern);
   p.setBrush(QPalette::Window,brush);
   dxfview->setPalette(p);


   }

   void MainWindow::creatbuttons()
   {
       textTop=new GcodeEdit(0);
       textBottom=new QPlainTextEdit(0);
       load=new QPushButton(QString::fromLocal8Bit("载入"),0);
       //count=new QPushButton(QObject::tr("count"),0);
       count=new QPushButton(QString::fromLocal8Bit("计数"),0);
       simulation=new QPushButton(QString::fromLocal8Bit("仿真"),0);
       send=new QPushButton(QString::fromLocal8Bit("发送"),0);
       finish=new QPushButton(QString::fromLocal8Bit("结束"),0);
       compiler=new QPushButton(QString::fromLocal8Bit("编译"),0);

       QSize iconSize(4,4);
       zoomInIcon = new QToolButton;
       zoomInIcon->setAutoRepeat(true);
       zoomInIcon->setAutoRepeatInterval(33);
       zoomInIcon->setAutoRepeatDelay(0);
       //zoomInIcon->setIcon(QPixmap("images//zoomin.png"));
       //zoomInIcon->setIconSize(QPixmap( "images//zoomin.png").size());
       zoomOutIcon = new QToolButton;
       zoomOutIcon->setAutoRepeat(true);
       zoomOutIcon->setAutoRepeatInterval(33);
       zoomOutIcon->setAutoRepeatDelay(0);
       // zoomOutIcon->setIcon(QPixmap(":/File/zoomout.png"));
       //zoomOutIcon->setIconSize(QPixmap("/File/zoomin.png").size());
       zoomSlider = new QSlider;
       zoomSlider->setMinimum(0);
       zoomSlider->setMaximum(500);
       zoomSlider->setValue(250);
       zoomSlider->setTickPosition(QSlider::TicksRight);

       // Zoom slider layout


       QVBoxLayout *zoomSliderLayout = new QVBoxLayout;
       zoomSliderLayout->addWidget(zoomInIcon);
       zoomSliderLayout->addWidget(zoomSlider);
       zoomSliderLayout->addWidget(zoomOutIcon);
       zoomwidget=new QWidget();
       zoomwidget->setLayout(zoomSliderLayout);
       //zoom in out

       selectGroup = new QGroupBox(0);
       //  selectGroup->setTitle(tr("select"));
       selectGroup->setTitle(QString::fromLocal8Bit("选择"));
       zhengjiaoType = new QRadioButton(selectGroup);
       zuijinType = new QRadioButton(selectGroup);
       zidingyiType= new QRadioButton(selectGroup);
       zhengjiaoType->setText(QString::fromLocal8Bit("正交"));
       zuijinType->setText(QString::fromLocal8Bit("最近点选择"));
       zidingyiType->setText(QString::fromLocal8Bit("自定义"));
       selectGroup->adjustSize();
       zhengjiaoType->setChecked(true);
       QVBoxLayout *vbox=new QVBoxLayout;
       vbox->addWidget(zhengjiaoType);
       vbox->addWidget(zuijinType);
       vbox->addWidget(zidingyiType);
       selectGroup->setLayout(vbox);

   }

   void MainWindow::creatsplitter()
   {

       QSplitter *splitterMain=new QSplitter(Qt::Horizontal,this);
       QSplitter *splitterLeft=new QSplitter(Qt::Vertical);
       QSplitter *splitterRight=new QSplitter(Qt::Vertical);
       QSplitter *splitterLeftUp=new QSplitter(Qt::Horizontal);
       QSplitter *splitterLeftDown=new QSplitter(Qt::Horizontal);

       QSplitter *splitterRightDown=new QSplitter(Qt::Horizontal);
      splitterLeftUp->addWidget(dxfview);
       splitterLeftUp->addWidget(zoomwidget);
       splitterLeft->addWidget(splitterLeftUp);
       splitterLeftDown->addWidget(count);
       splitterLeftDown->addWidget(load);
       splitterLeftDown->addWidget(selectGroup);
       splitterLeft->addWidget(splitterLeftDown);


       splitterMain->addWidget(splitterLeft);

       splitterRight->addWidget(textTop);
       splitterRight->addWidget(textBottom);

       splitterRightDown->addWidget(compiler);
      splitterRightDown->addWidget(simulation);
      splitterRightDown->addWidget(send);
      splitterRightDown->addWidget(finish);

      splitterRight->addWidget(splitterRightDown);
       //splitterRight->setOpaqueResize(false);
       splitterMain->addWidget(splitterRight);
       splitterMain->setStretchFactor(1,1);
       splitterMain->setWindowTitle(QObject::tr("dxf"));
         // splitterMain->show();
       this->setCentralWidget(splitterMain);
   }

   void MainWindow::creatconnect()
   {
       //slot
       connect(load, SIGNAL(clicked()), this, SLOT(openfile()));
       connect(count, SIGNAL(clicked()), this, SLOT(countholl()));
       connect(send,SIGNAL(clicked()),this,SLOT(wirtecomm()));
       connect(time,SIGNAL(timeout()),this,SLOT(readcomm()));//定时溢出实现读串口操作
       connect(finish,SIGNAL(clicked()),this,SLOT(closeThread()));//测试用的
       connect(compiler,SIGNAL(clicked()),this->textTop,SLOT(compilegcode()));
       //        connect(commthread,SIGNAL(finished()),this,SLOT(displaycomm()));      //接收信号实现显示
       connect(simulation,SIGNAL(clicked()),this,SLOT(simulater()));
       connect(zoomInIcon, SIGNAL(clicked()), this, SLOT(zoomIn()));
       connect(zoomOutIcon, SIGNAL(clicked()), this, SLOT(zoomOut()));
       connect(zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(setupMatrix()));
       connect(configAct, SIGNAL(triggered()),
               this, SLOT(configsetting()));
       connect(openIniFileAct,SIGNAL(triggered()),
               this,SLOT(openfile()));
   }

   void MainWindow::createMenus()
    {
        fileMenu = menuBar()->addMenu(QString::fromLocal8Bit("文件"));
        fileMenu->addAction(openSettingsAct);
        fileMenu->addAction(openIniFileAct);
        fileMenu->addAction(openPropertyListAct);
        fileMenu->addAction(openRegistryPathAct);
        fileMenu->addSeparator();
        fileMenu->addAction(refreshAct);
        fileMenu->addSeparator();
        fileMenu->addAction(exitAct);

        optionsMenu = menuBar()->addMenu(QString::fromLocal8Bit("设置"));
        optionsMenu->addAction(autoRefreshAct);
        optionsMenu->addAction(fallbacksAct);
        optionsMenu->addAction(configAct);

        menuBar()->addSeparator();

       // helpMenu = menuBar()->addMenu(tr("&Help"));
         helpMenu = menuBar()->addMenu(QString::fromLocal8Bit("帮助"));
        helpMenu->addAction(aboutAct);
        helpMenu->addAction(aboutQtAct);
    }

    void MainWindow::openfile()
    {
             //path = QFileDialog::getOpenFileName(this, tr("Open dxf file"), ".", tr("dxf Files(*.dwg *.dxf)"));
            path = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("打开dxf文件"), ".", tr("dxf Files(*.dwg *.dxf)"));
              if(path.length() == 0) {
                     // QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
                   QMessageBox::information(NULL, tr("Path"), QString::fromLocal8Bit("没有选择文件"));
              } else {
                     // QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path);
                      QMessageBox::information(NULL, tr("Path"), QString::fromLocal8Bit("选择") + path);
              }
              loadFile();
    }

    void MainWindow::loadFile()
    {
        dxfscene->clear();
        CIRCLEREAD *circleread=new CIRCLEREAD();
        QByteArray ba=path.toLatin1();
        const char *filename=ba.data();
        circleread->readcircle(filename);
        double temp=0;
        double radiustemp=0;


        QList<DL_CircleData>::iterator circle=
                circleread->circlelist.begin();
        while (circle != circleread->circlelist.end())
        {
            if ((temp+radiustemp)<=((*circle).cy+(*circle).radius))
            {
                temp=(*circle).cy;
                radiustemp=(*circle).radius;
            }
            circle++;
        }

        qDebug("the max y is :%lf",temp+radiustemp);


      //生成hole
        QList<DL_CircleData>::iterator circledraw=
                circleread->circlelist.begin();
        while (circledraw != circleread->circlelist.end())
        {
            Hole *holetemp=new Hole((*circledraw).cx,temp+radiustemp-(*circledraw).cy,(*circledraw).radius);
            holetemp->setFlags(QGraphicsItem::ItemIsSelectable);
            holetemp->installEventFilter(this);
            holeVec.append(holetemp);
            dxfscene->addItem(holetemp);

            circledraw++;
       }
//读取多边形
//        if (!(circleread->polylinelist.isEmpty()))
//        {
//            qDebug("the polylinelist is not empty");
//            QList <DL_PolylineData>::iterator polylineit=
//                    circleread->polylinelist.begin();
//            QList <DL_VertexData>::iterator vertexit=
//                    circleread->vertexlist.begin();
//            while (polylineit !=circleread->polylinelist.end())
//            {
//                qDebug()<<(*polylineit).flags<<(*polylineit).number<<"\n";
//                if((*polylineit).number != 0)
//                {
//                    QVector<QPoint>  points;
//                    for (int j=0;j<(*polylineit).number;j++)
//                    {
//                        qDebug()<<(*vertexit).x<<" "<<(*vertexit).y<<"\n";
//                        QPoint *pointemp=new QPoint((*vertexit).x,(*vertexit).y);
//                        points<<*pointemp;
//                        vertexit++;
//                    }
//                    //QPolygonF  polygonf;
//                    //polygonf=new QPolygonF(points,0);
//                    QGraphicsPolygonItem
//                            *polyitem=new QGraphicsPolygonItem(QPolygonF(points));
//                    polyitem->setBrush(Qt::red);
//                    dxfscene->addItem(polyitem);
//                }
//                polylineit++;

//            }
//                }


        //尝试调用dxf2gcode外部程序
//        qDebug()<<"start dxf2gcode\n";
//        QProcess *togcode=new QProcess(this);
//        QString programname="dxf2gcode";
//        QStringList arguments;
//        QString outputfilename=QString(filename)+"gcode";
//        arguments<<"-f"<<filename<<"-e"<<outputfilename<<"-q";
//        togcode->start(programname,arguments);

//        if(!togcode->waitForStarted())
//        {
//            qDebug()<<"start error\n";

//        }
//        QByteArray procOutput;
//        while (false==togcode->waitForFinished()) {
//            qDebug()<<"the proc is waitting";

//        }
//        procOutput=togcode->readAll();
//         qDebug()<<procOutput;


    }
   //接受view传递过来的被选中的item
    void MainWindow::selectitem(Hole *hole)
    {
        qDebug()<<"mainwindow: You selected hole x:"<<hole->gethx();
        qDebug()<<"mainwindow:You selected  hole y:"<<hole->gethy();
    }

    void MainWindow::configsetting()
    {
        configdialog=new ConfigDialog;
        configdialog->exec();
    }

    void MainWindow::countholl()
    {
        std::sort(holeVec.begin(),holeVec.end(),CompLessX());
        for (int i=0;i<holeVec.size();i++)
        {
            qDebug("the %d x is:%lf,y is:%lf,radius is:%lf",i+1,holeVec[i]->hx,holeVec[i]->hy,
                   holeVec[i]->hradius);
        }

        std::sort(holeVec.begin(),holeVec.end(),CompGreaterYX());
        for (int i=0;i<holeVec.size();i++)
        {
            qDebug("the %d x is:%lf,y is:%lf,radius is:%lf",i+1,holeVec[i]->hx,holeVec[i]->hy,
                   holeVec[i]->hradius);
        }
      // zhengjiaosort();
        if(zhengjiaoType->isChecked())
        {
            zhengjiaosort();
        }
        else{
              nearpointpath();
        }


      generategcode();

    }

  // 写数据至串口
  void MainWindow::wirtecomm()
    {
        //commthread->write_rs=1;
        for (int i=1;i<holeVec.size();i++)
        {
            message tmpmsg=generatemessage(holeVec[i],holeVec[i-1]);
            for (int j=0;j<tmpmsg.messagearray.size();j++)
            {
                qDebug(" the %d message%d: %x",i, j, tmpmsg.messagearray.at(j));
            }
            hcomm->write(tmpmsg.messagearray);
        }

//          hcomm->write(textTop->toPlainText().toAscii());
    }

    message MainWindow::generatemessage(Hole* hole1, Hole* hole2)
    {
          qint32 tempx=(int)((hole1->hx-hole2->hx)*10000+0.5)/10000.00;  //求精度，米为单位，精度为0.1毫米
          qint32 tempy=(int)((hole1->hy-hole2->hy)*10000+0.5)/10000.00;
          qDebug()<<"this is tested the get pulses start: ";
          qint32 testxpulses=stepPulses(tempx,setobj->leadx,setobj->xstepangle);
           qDebug("the  pulses is :%d",testxpulses);
          qDebug()<<"this is tested the get pulses end! ";

          QByteArray commandarr1;
          QDataStream comm(&commandarr1,QIODevice::WriteOnly);
          comm<<tempx;
          quint8  tempcomm=movex;
          quint16 tempcrc=0;
          message msg(tempcomm,commandarr1,tempcrc);
          return msg;

    }
    //安装事件过滤器，view上的鼠标响应事件
    bool MainWindow::eventFilter(QObject *target, QEvent *event)
    {
   //     if(target==dxfview)
            if(target->inherits("Hole"))
        {
            if(event->type()==QEvent::MouseButtonPress)
            {
                QMouseEvent *me=static_cast<QMouseEvent*>(event);
                if(me->button()==Qt::LeftButton)
                {
                    qDebug()<<"the mainwindow receive the scene click ";
                    return true;
                }
                else{
                    return false;
                }

            }
            else
            {return false;}
        }
        else {
            return QMainWindow::event(event);
        }
    }
  //读数据串口
    void MainWindow::readcomm()
    {
     //   commthread->read_rs=1;
       //qDebug("serior point is reading");
        quint8 head;
        quint8 rececomm;
        quint8 recelength;
        quint32 data;
        QByteArray recearray;

        if (hcomm->bytesAvailable()>=8)
        {
           // qDebug()<<"read :"<<hcomm->bytesAvailable()<<"bytes";
            QByteArray readtemp=hcomm->readAll();
            QDataStream commread(&readtemp,QIODevice::ReadOnly);
            while(!commread.atEnd())
            {
                commread>>head>>rececomm>>recelength>>data;
//                if(recelength!=0)
//                {
//                       recearray=readtemp.mid(3,recelength);
//                }

            }
//            char *ch;
//            ch=readtemp.data();
//            textBottom->insertPlainText(ch);
            qDebug()<<head;
            qDebug()<<rececomm;
            qDebug()<<recelength;
            //qDebug()<<recearray;
            textBottom->insertPlainText(QString::number(head,16));
            textBottom->insertPlainText(QString::number(rececomm,16));
            textBottom->insertPlainText(QString::number(recelength,16));
            textBottom->insertPlainText(QString::number(data,16));
           // textBottom->insertPlainText(recearray);
        }
    }

    void MainWindow::closeThread()
    {
        QList<QGraphicsItem*> temptest;
        temptest=dxfscene->selectedItems();
        for(int i=0;i<temptest.size();i++)
        {
            if (Hole *holetemp1=qgraphicsitem_cast<Hole*>(temptest.at(i)))
            qDebug("the hole %d x is:%lf,y is:%lf,radius is:%lf",i+1,holetemp1->hx,holetemp1->hy,
                    holetemp1->hradius);
         }
        }


//    void MainWindow::closeThread()
//    {
//        commthread->stopped=0;
//    }

//    void MainWindow::displaycomm()
//    {
//        textBottom->setText(commthread->buf);
//    }

    void MainWindow::simulater()
    {
        int blocknum=0;
        QTextCursor tc = textTop->textCursor();
        tc.setPosition(0,QTextCursor::MoveAnchor);
        textTop->setTextCursor(tc);
        for (int i=0;i<holeVec.size();i++)
        {
            //视图仿真
            holeVec[i]->hcolor=Qt::green;
            holeVec[i]->update();
            //G代码高亮并传串口
            //gotoline(blocknum);
            textTop->gotoline(blocknum);
            //highlightCurrentLine();
            textTop->highlightCurrentLine();
            hcomm->write(textTop->document()->findBlockByNumber(blocknum).text().toAscii());
            blocknum=blocknum+1;
            //gotoline(blocknum);
            textTop->gotoline(blocknum);
//            highlightCurrentLine();
            textTop->highlightCurrentLine();
            hcomm->write(textTop->document()->findBlockByNumber(blocknum).text().toAscii());
            //延时
            QElapsedTimer t;
            t.start();
            while(t.elapsed()<1000)
                  QCoreApplication::processEvents();
      }
    }

//    void MainWindow::gotoline(int line)
//    {
//        QTextCursor tc = textTop->textCursor();

//        int  position  =  textTop->document()-> findBlockByNumber ( line - 1  ).position();
//         tc.setPosition(position,QTextCursor::MoveAnchor);
//         //tc.select(QTextCursor::LineUnderCursor);//选中整行
//         textTop->setTextCursor(tc);
//    }

//    void MainWindow::highlightCurrentLine()
//    {
//        QList<QTextEdit::ExtraSelection> extraSelections;

//        if (!textTop->isReadOnly()) {
//            QTextEdit::ExtraSelection selection;

//            QColor lineColor = QColor(Qt::blue).lighter(160);

//            selection.format.setBackground(lineColor);
//            selection.format.setProperty(QTextFormat::FullWidthSelection, true);
//            selection.cursor = textTop->textCursor();
//            selection.cursor.clearSelection();
//            extraSelections.append(selection);
//        }

//        textTop->setExtraSelections(extraSelections);
//    }
     //正交排序
  void    MainWindow::zhengjiaosort( )
    {
      int countline=1;
      for (int i=1;i<holeVec.size();i++)
      {
          if (holeVec[i]->hy !=holeVec[i-1]->hy)
          {

              countline++;
              if (countline%2==0)
              {
                  int readi=0;
                  while(holeVec[i]->hy==holeVec[i+readi]->hy)
                  {
                      readi++;
                  }
                  std::sort(holeVec.begin()+i,holeVec.begin()+i+readi, CompGreaterX());
                  i=i+readi;
              }

          }
      }
  }
  //最近点排序
  void MainWindow::nearpointpath()
  {

     // 最近点路径法
              std::sort(holeVec.begin(),holeVec.end(),CompTwoHole(*holeVec.begin()));
             // QVector<Hole*> holetmp;
              for (int i=1;i<holeVec.size();i++)
              {
                  std::sort(holeVec.begin()+i,holeVec.end(),CompTwoHole(*(holeVec.begin()+i)));
              }

              // 最近点路径法
  }
  //gcode generate
  void MainWindow::generategcode()
  {
      //原来程序
      for (int i=1;i<holeVec.size();i++)
      {
          QString gcodetemp;

          //gcodetemp=QString("G00 X%1 Y%2 ").arg(QString::number(holeVec[i]->hx,'f',6)).arg(QString::number(holeVec[i]->hy,'f',6));
          gcodetemp=QString("G00 X%1 Y%2 ").arg(QString::number(stepPulses(holeVec[i]->hx-holeVec[i-1]->hx,setobj->leadx,setobj->xstepangle))).\
                  arg(QString::number(stepPulses(holeVec[i]->hy-holeVec[i-1]->hy,setobj->leady,setobj->ystepangle)));

          qDebug()<<gcodetemp;
          textTop->appendPlainText(gcodetemp);

//          gcodetemp=QString("G20 R%1 S%2 A%3 L%4 D%5").arg(QString::number(holeVec[i]->hradius)).arg(0).arg(90).arg(1).arg(1);
//          qDebug()<<gcodetemp;
//          textTop->appendPlainText(gcodetemp);
      }

      //读取dxf2gcode生成的文件

//      QString filename=filename+"gcode.ngc";
//      QFile file(filename);
//      file.open(QIODevice::ReadOnly);
//      QDataStream ts(&file);
////      while (ts.atEnd()) {

////      }
//      QString str;
//      ts>>str;
//      qDebug()<<str;
//      textTop->appendPlainText(str);
//读取dxf2gcode生成的文件
  }



  void MainWindow::zoomIn()
    {
         zoomSlider->setValue(zoomSlider->value() + 1);
    }

    void MainWindow::zoomOut()
    {
       zoomSlider->setValue(zoomSlider->value() - 1);
    }

    void MainWindow::setupMatrix()
    {
        qreal scale = qPow(qreal(2), (zoomSlider->value() - 250) / qreal(50));

        QMatrix matrix;
        matrix.scale(scale, scale);

        dxfview->setMatrix(matrix);

    }

//    void MainWindow::connectItem(QGraphicsItem *item)
//    {
////        connect(item, SIGNAL(dirty()), this, SLOT(setDirty()));
////        const QMetaObject *metaObject = item->metaObject();
////        if (metaObject->indexOfProperty("brush") > -1)
////            connect(brushWidget, SIGNAL(brushChanged(const QBrush&)),
////                    item, SLOT(setBrush(const QBrush&)));
////        if (metaObject->indexOfProperty("pen") > -1)
////            connect(penWidget, SIGNAL(penChanged(const QPen&)),
////                    item, SLOT(setPen(const QPen&)));
////        if (metaObject->indexOfProperty("angle") > -1) {
////            connect(transformWidget, SIGNAL(angleChanged(double)),
////                    item, SLOT(setAngle(double)));
////            connect(transformWidget, SIGNAL(shearChanged(double, double)),
////                    item, SLOT(setShear(double, double)));
////        }
        
//        connect(item,SIGNAL())
//    }



