/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>
#include "common.h"
#include "pages.h"
#include <QSettings>
#include "settingobject.h"
#include <QLineEdit>


//settingobject *setobj=new settingobject();
ConfigurationPage::ConfigurationPage(QWidget *parent)
    : QWidget(parent)
{


    QGroupBox *configGroup = new QGroupBox(QString::fromLocal8Bit("参数设置"));

    QGroupBox *screwGroup=new QGroupBox(QString::fromLocal8Bit("丝杠导程"));
    QLabel *xlead = new QLabel(QString::fromLocal8Bit("x导程"));
    xleadlineEdit = new QLineEdit();

    xleadlineEdit->setText(QString::number((setobj->leadx),'f',2));
    QLabel *xleadmm=new QLabel(tr("mm"));

    QLabel *ylead = new QLabel(QString::fromLocal8Bit("y导程"));
    yleadlineEdit = new QLineEdit;
    yleadlineEdit->setText(QString::number((setobj->leady),'f',2));
    QLabel *yleadmm=new QLabel(tr("mm"));

//    serverCombo->addItem(tr("Qt (USA)"));

    QHBoxLayout *screwlayout = new QHBoxLayout;
    screwlayout->addWidget(xlead);
    screwlayout->addWidget(xleadlineEdit);
    screwlayout->addWidget(xleadmm);
    screwlayout->addWidget(ylead);
    screwlayout->addWidget(yleadlineEdit);
    screwlayout->addWidget(yleadmm);

    QVBoxLayout *configLayout1= new QVBoxLayout;
    configLayout1->addLayout(screwlayout);
    screwGroup->setLayout(configLayout1);

    QGroupBox *xstepangleGroup=new QGroupBox(QString::fromLocal8Bit("x向电机"));
    QLabel *xstepanglelable = new QLabel(QString::fromLocal8Bit("步距角"));
    xstepangleinput = new QLineEdit;
    xstepangleinput->setText(QString::number((setobj->xstepangle),'f',2));
    QLabel *degree1=new QLabel(tr("度"));

    QHBoxLayout *xstepanglelayout = new QHBoxLayout;
    xstepanglelayout->addWidget(xstepanglelable);
    xstepanglelayout->addWidget(xstepangleinput);
    xstepanglelayout->addWidget(degree1);

    QVBoxLayout *configLayout2= new QVBoxLayout;
    configLayout2->addLayout(xstepanglelayout);
    xstepangleGroup->setLayout(configLayout2);

    QGroupBox *ystepangleGroup=new QGroupBox(QString::fromLocal8Bit("y向电机"));
    QLabel *ystepanglelable = new QLabel(QString::fromLocal8Bit("步距角"));
    ystepangleinput = new QLineEdit;
    ystepangleinput->setText(QString::number((setobj->ystepangle),'f',2));
    QLabel *degree2=new QLabel(tr("度"));

    QHBoxLayout *ystepanglelayout = new QHBoxLayout;
    ystepanglelayout->addWidget(ystepanglelable);
    ystepanglelayout->addWidget(ystepangleinput);
    ystepanglelayout->addWidget(degree2);

    QVBoxLayout *configLayout3= new QVBoxLayout;
    configLayout3->addLayout(ystepanglelayout);
    ystepangleGroup->setLayout(configLayout3);

    QHBoxLayout *mainconfigLayoutup= new QHBoxLayout;

    mainconfigLayoutup->addWidget(screwGroup);
    mainconfigLayoutup->addStretch(4);
    mainconfigLayoutup->addWidget(xstepangleGroup);
    mainconfigLayoutup->addStretch(4);
    mainconfigLayoutup->addWidget(ystepangleGroup);

    QGroupBox *maxstepangleGroup=new QGroupBox(QString::fromLocal8Bit("最大步距"));
    QLineEdit   *maxstepangleinput = new QLineEdit;
    QLabel *maxstep=new QLabel(tr("毫米"));

    QHBoxLayout *maxstepanglelayout = new QHBoxLayout;
    maxstepanglelayout->addWidget(maxstepangleinput);
    maxstepanglelayout->addWidget(maxstep);


    QVBoxLayout *configLayout4= new QVBoxLayout;
    configLayout4->addLayout(maxstepanglelayout);
    maxstepangleGroup->setLayout(configLayout4);


    QVBoxLayout *mainconfiglayout=new QVBoxLayout;
    mainconfiglayout->addLayout(mainconfigLayoutup);
    mainconfiglayout->addWidget(maxstepangleGroup);
    configGroup->setLayout(mainconfiglayout);

    ConfigUpdateButton = new QPushButton(tr(" update"));

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addWidget(configGroup);
    mainLayout->addWidget(ConfigUpdateButton);
    mainLayout->addStretch(4);

    setLayout(mainLayout);

    connect(xleadlineEdit,SIGNAL(textEdited(QString)),this,SLOT(lineeditchange(QString)));
    connect(yleadlineEdit,SIGNAL(textEdited(QString)),this,SLOT(lineeditchange(QString)));

//    connect(xleadlineEdit,SIGNAL(textEdited(const QString &)),this,SLOT(xleadchange(const QString& ));

    connect(ConfigUpdateButton,SIGNAL(clicked()),this,SLOT(updateconfig()));
}

void ConfigurationPage::updateconfig()
{


    setobj->updatesetting();
}

void ConfigurationPage::lineeditchange(QString text)
{
    //QObject* Isender=sender();
    QLineEdit *ISender=dynamic_cast<QLineEdit* >(sender());
    if (ISender==0)
    {
        return;
    }
    else if (ISender==xleadlineEdit)
    {
            double leadx=text.toDouble();
            setobj->leadx=leadx;
    }

    else if (ISender==yleadlineEdit)
    {
            double leady=text.toDouble();
            setobj->leady=leady;
    }

}

UpdatePage::UpdatePage(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *CadsettingGroup=new QGroupBox(QString::fromLocal8Bit("加工幅面设置"));
    QLabel *dxflong = new QLabel(QString::fromLocal8Bit("板料长"));
    QLineEdit  *dxflonglineEdit = new QLineEdit();

    dxflonglineEdit->setText(QString::number((setobj->leadx),'f',2));
    QLabel *dxflongmm=new QLabel(tr("mm"));

    QLabel *dxfwidth = new QLabel(QString::fromLocal8Bit("板料宽"));
    QLineEdit   *dxfwidthlineEdit = new QLineEdit();
    dxfwidthlineEdit->setText(QString::number((setobj->leady),'f',2));
    QLabel *dxfwidthmm=new QLabel(tr("mm"));

//    serverCombo->addItem(tr("Qt (USA)"));

    QHBoxLayout *dxfsettinglayout = new QHBoxLayout;
    dxfsettinglayout->addWidget(dxflong);
    dxfsettinglayout->addWidget(dxflonglineEdit);
    dxfsettinglayout->addWidget(dxflongmm);
    dxfsettinglayout->addWidget(dxfwidth);
    dxfsettinglayout->addWidget(dxfwidthlineEdit);
    dxfsettinglayout->addWidget(dxfwidthmm);

    QVBoxLayout *dxfconfigLayout= new QVBoxLayout;
    dxfconfigLayout->addLayout(dxfsettinglayout);
    CadsettingGroup->setLayout(dxfconfigLayout);

    QPushButton   *ConfigUpdateButton = new QPushButton(tr(" update"));

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addWidget(CadsettingGroup);
    mainLayout->addWidget(ConfigUpdateButton);
    mainLayout->addStretch(4);

    setLayout(mainLayout);

}

QueryPage::QueryPage(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *packagesGroup = new QGroupBox(tr("Look for packages"));

    QLabel *nameLabel = new QLabel(tr("Name:"));
    QLineEdit *nameEdit = new QLineEdit;

    QLabel *dateLabel = new QLabel(tr("Released after:"));
    QDateTimeEdit *dateEdit = new QDateTimeEdit(QDate::currentDate());

    QCheckBox *releasesCheckBox = new QCheckBox(tr("Releases"));
    QCheckBox *upgradesCheckBox = new QCheckBox(tr("Upgrades"));

    QSpinBox *hitsSpinBox = new QSpinBox;
    hitsSpinBox->setPrefix(tr("Return up to "));
    hitsSpinBox->setSuffix(tr(" results"));
    hitsSpinBox->setSpecialValueText(tr("Return only the first result"));
    hitsSpinBox->setMinimum(1);
    hitsSpinBox->setMaximum(100);
    hitsSpinBox->setSingleStep(10);

    QPushButton *startQueryButton = new QPushButton(tr("Start query"));

    QGridLayout *packagesLayout = new QGridLayout;
    packagesLayout->addWidget(nameLabel, 0, 0);
    packagesLayout->addWidget(nameEdit, 0, 1);
    packagesLayout->addWidget(dateLabel, 1, 0);
    packagesLayout->addWidget(dateEdit, 1, 1);
    packagesLayout->addWidget(releasesCheckBox, 2, 0);
    packagesLayout->addWidget(upgradesCheckBox, 3, 0);
    packagesLayout->addWidget(hitsSpinBox, 4, 0, 1, 2);
    packagesGroup->setLayout(packagesLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(packagesGroup);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(startQueryButton);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}
