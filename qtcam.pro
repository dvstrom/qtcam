#-------------------------------------------------
#
# Project created by QtCreator 2013-11-01T15:35:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtcam
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    src/dl_writer_ascii.cpp \
    src/dl_dxf.cpp \
    circleread.cpp \
    hole.cpp \
    dxfview.cpp \
    qextserialbase.cpp \
    posix_qextserialport.cpp \
    message.cpp \
    pages.cpp \
    configdialog.cpp \
    settingobject.cpp \
    common.cpp \
    gcodeparse.cpp \
    gcodeedit.cpp

HEADERS  += mainwindow.h \
    src/dl_writer_ascii.h \
    src/dl_writer.h \
    src/dl_extrusion.h \
    src/dl_exception.h \
    src/dl_entities.h \
    src/dl_dxf.h \
    src/dl_creationinterface.h \
    src/dl_creationadapter.h \
    src/dl_codes.h \
    src/dl_attributes.h \
    circleread.h \
    hole.h \
    dxfview.h \
    qextserialbase.h \
    posix_qextserialport.h \
    message.h \
    itemtypes.h \
    pages.h \
    configdialog.h \
    settingobject.h \
    common.h \
    gcodeedit.h \
    gcodeparse.h


OTHER_FILES += \
    src/dl_writer_ascii.o \
    src/dl_dxf.o
sources.files = $$SOURCES $$HEADERS $$RESOURCES *.pro images
#unix:!macx: LIBS += -L$$PWD/ -ldxflib
LIBS += $$PWD/libdxflib.a
INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/
INCLUDEPATH += src/
unix:!macx: PRE_TARGETDEPS += $$PWD/libdxflib.a
