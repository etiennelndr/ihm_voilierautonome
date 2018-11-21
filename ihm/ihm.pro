#-------------------------------------------------
#
# Project created by QtCreator 2018-10-17T17:23:39
#
#-------------------------------------------------

QT       += core gui network widgets

greaterThan(QT_MAJOR_VERSION, 4)

TARGET = ihm
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

DEPENDPATH += . include main src src/utils
INCLUDEPATH += . include include/utils

SOURCES += \
    main\main.cpp \
    src\mainwindow.cpp \
    src\client.cpp \
    src\message.cpp \
    src\boat.cpp \
    src\virtualmap.cpp \
    src\balises.cpp \
    src\sationsmeteo.cpp \
    src\stationsmeteo2.cpp \
    src\meteo.cpp \
    src\utils\utils.cpp \
    src/balise.cpp

HEADERS += \
    include\mainwindow.h \
    include\client.h \
    include\message.h \
    include\boat.h \
    include\virtualmap.h \
    include\balises.h \
    include\sationsmeteo.h \
    include\stationsmeteo2.h\
    include\meteo.h \
    include\utils\utils.h \
    include/balise.h

FORMS += \
    forms\mainwindow.ui \
    forms\balises.ui \
    forms\sationsmeteo.ui \
    forms\stationsmeteo2.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
