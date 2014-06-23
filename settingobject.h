#ifndef SETTINGOBJECT_H
#define SETTINGOBJECT_H

#include <QObject>

class settingobject : public QObject
{
    Q_OBJECT
public:
    explicit settingobject(QObject *parent = 0);
    void setleadx(double arg);
    double getleadx();
    void setleady(double arg);
    double getleady();
    void setxstepangle(double arg);
    void getxstepangle();
    void setystepangle(double arg);
    void getystepangle();

    void setlow_initspeed(double arg);
    double getlow_initspeed();
    void setlow_endspeed(double arg);
    double getlow_endspeed();
    void setlow_acceleratedspeed(double arg);
    double getlow_acceleratedspeed();

    void setlowmed_initspeed(double arg);
    double getlowmed_initspeed();
    void setlowmed_endspeed(double arg);
    double getlowmed_endspeed();
    void setlowmed_acceleratedspeed(double arg);
    double getlowmed_acceleratedspeed();

    void setmed_initspeed(double arg);
    double getmed_initspeed();
    void setmed_endspeed(double arg);
    double getmed_endspeed();
    void setmed_acceleratedspeed(double arg);
    double getmed_acceleratedspeed();

    void sethighmed_initspeed(double arg);
    double gethighmed_initspeed();
    void sethighmed_endspeed(double arg);
    double gethighmed_endspeed();
    void sethighmed_acceleratedspeed(double arg);
    double gethighmed_acceleratedspeed();

    void sethigh_initspeed(double arg);
    double gethigh_initspeed();
    void sethigh_endspeed(double arg);
    double gethigh_endspeed();
    void sethigh_acceleratedspeed(double arg);
    double gethigh_acceleratedspeed();

    void updatesetting();
signals:

public slots:

public:
    //丝杠导程
    double leadx;
    double leady;
    //x，y向步进电机步距角
    double xstepangle;
    double ystepangle;
    //低速设置(初速、末速、加速）
    double low_initspeed;
    double low_endspeed;
    double low_acceleratedspeed;
    //中低速设置
    double lowmed_initspeed;
    double lowmed_endspeed;
    double lowmed_acceleratedspeed;
    //中速设置
    double med_initspeed;
    double med_endspeed;
    double med_acceleratedspeed;
    //中高速设置
    double highmed_initspeed;

    double highmed_endspeed;
    double highmed_acceleratedspeed;
    //高速设置
    double high_initspeed;
    double high_endspeed;
    double high_acceleratedspeed;
};

#endif // SETTINGOBJECT_H
