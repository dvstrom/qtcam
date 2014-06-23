#include "settingobject.h"
#include <QFile>
#include <QSettings>
settingobject::settingobject(QObject *parent) :
    QObject(parent)
{
    QString filename="config.ini";
    if(!QFile::exists(filename))
    {
        QSettings setting("config.ini",QSettings::IniFormat);
        setting.beginGroup("screw");
        setting.setValue("leadx","16");
        setting.setValue("leady","24");
        setting.endGroup();

        setting.beginGroup("xstepangle");
        setting.setValue("stepanglex","9");
        setting.endGroup();

        setting.beginGroup("ystepangle");
        setting.setValue("stepangley","75");
        setting.endGroup();

        setting.beginGroup("lowspeed");
        setting.setValue("low_initspeed","1");
        setting.setValue("low_endspeed","10");
        setting.setValue("low_acceleratedspeed","15000");
        setting.endGroup();

        setting.beginGroup("lowmedspeed");
        setting.setValue("lowmed_initspeed","1");
        setting.setValue("lowmed_endspeed","12");
        setting.setValue("lowmed_acceleratedspeed","18000");
        setting.endGroup();

        setting.beginGroup("medspeed");
        setting.setValue("med_initspeed","1");
        setting.setValue("med_endspeed","15");
        setting.setValue("med_acceleratedspeed","20000");
        setting.endGroup();

        setting.beginGroup("highmedspeed");
        setting.setValue("highmed_initspeed","1");
        setting.setValue("highmed_endspeed","16");
        setting.setValue("highmed_acceleratedspeed","22000");
        setting.endGroup();

        setting.beginGroup("highspeed");
        setting.setValue("high_initspeed","1");
        setting.setValue("high_endspeed","20");
        setting.setValue("high_acceleratedspeed","22000");
        setting.endGroup();



    }
    else
    {
        QSettings setting("config.ini",QSettings::IniFormat);
        leadx=setting.value("screw/leadx",16).toDouble();
        leady=setting.value("screw/leady",24).toDouble();

        xstepangle=setting.value("xstepangle/stepanglex",9).toDouble();
        ystepangle=setting.value("ystepangle/stepangley",75).toDouble();

        low_initspeed=setting.value("lowspeed/low_initspeed",1).toDouble();
        low_endspeed=setting.value("lowspeed/low_endspeed",10).toDouble();
        low_acceleratedspeed=setting.value("lowspeed/low_acceleratedspeed",15000).toDouble();

        lowmed_initspeed=setting.value("lowmedspeed/lowmed_initspeed",1).toDouble();
        lowmed_endspeed=setting.value("lowmedspeed/lowmed_endspeed",10).toDouble();
        lowmed_acceleratedspeed=setting.value("lowmedspeed/lowmed_acceleratedspeed",15000).toDouble();

        med_initspeed=setting.value("medspeed/med_initspeed",1).toDouble();
        med_endspeed=setting.value("medspeed/med_endspeed",15).toDouble();
        med_acceleratedspeed=setting.value("medspeed/med_acceleratedspeed",18000).toDouble();

        highmed_initspeed=setting.value("highmedspeed/highmed_initspeed",1).toDouble();
        highmed_endspeed=setting.value("highmedspeed/highmed_endspeed",16).toDouble();
        highmed_acceleratedspeed=setting.value("highmedspeed/highmed_acceleratedspeed",22000).toDouble();

        high_initspeed=setting.value("highspeed/high_initspeed",1).toDouble();
        high_endspeed=setting.value("highspeed/high_endspeed",20).toDouble();
        high_acceleratedspeed=setting.value("highspeed/high_acceleratedspeed",22000).toDouble();

    }

}

void settingobject::updatesetting()
{
    QSettings setting("config.ini",QSettings::IniFormat);
    setting.setValue("screw/leadx",this->leadx);
    setting.setValue("screw/leady",this->leady);

}
