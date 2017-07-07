#-------------------------------------------------
#
# Project created by QtCreator 2017-06-24T10:00:26
#
#-------------------------------------------------

QT       += core gui  xml   network  xlsx

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mydemo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    myhelper.cpp \
    parklotupdate.cpp \
    mytcpserver.cpp \
    baseclass.cpp \
    myaction.cpp


HEADERS += \
    parklotupdate.h \
    mytcpserver.h \
    baseclass.h \
    myaction.h \
    myhelper.h

CONFIG += C++11

LIBS += -L$$PWD/3rdparty/windows/lib -lVersion
LIBS += -L$$PWD/3rdparty/Crypto/lib -lcryptlib -lcryptopp -llibcryptopp-CRYPTOPP_5_6_5
LIBS += -L$$PWD/3rdparty/7zip/lib -lLzmaUtil
LIBS += -L$$PWD/3rdparty/qmqtt/lib -llibqmqttd
LIBS += -L$$PWD/3rdparty/QtXlsx/lib -llibQt5Xlsxd


INCLUDEPATH += $$PWD/3rdparty/Crypto/include
INCLUDEPATH += $$PWD/3rdparty/7zip/include
INCLUDEPATH += $$PWD/3rdparty/qmqtt/include
INCLUDEPATH += $$PWD/3rdparty/QtXlsx/include

DEPENDPATH += $$PWD/.
