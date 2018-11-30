#-------------------------------------------------
#
# Project created by QtCreator 2018-11-10T19:22:58
#
#-------------------------------------------------

QT       += core gui
QT       += xml
QT       += quick
QT       += qml quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Forum
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


SOURCES += main.cpp\
        mainwindow.cpp \
    user.cpp \
    administrator.cpp \
    login.cpp \
    basewindow.cpp \
    mytitlebar.cpp \
    post.cpp \
    comment.cpp \
    plate.cpp

HEADERS  += mainwindow.h \
    user.h \
    administrator.h \
    header.h \
    login.h \
    basewindow.h \
    mytitlebar.h \
    post.h \
    comment.h \
    plate.h

FORMS    += mainwindow.ui \
    plate.ui

DISTFILES += \
    Plate.qml

RESOURCES += \
    resource.qrc
