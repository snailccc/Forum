#-------------------------------------------------
#
# Project created by QtCreator 2018-12-08T10:15:55
#
#-------------------------------------------------

QT       += core gui
QT       += core sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Forum2
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
    loginview.cpp \
    user.cpp \
    plate.cpp \
    comment.cpp \
    post.cpp

HEADERS  += mainwindow.h \
    loginview.h \
    user.h \
    global.h \
    plate.h \
    comment.h \
    post.h

FORMS    += mainwindow.ui \
    appoint.ui \
    comment.ui \
    plate.ui \
    post.ui \
    postMange.ui \
    public.ui \
    user_info.ui \
    login.ui \
    signin.ui
