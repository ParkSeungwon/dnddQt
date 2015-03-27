#-------------------------------------------------
#
# Project created by QtCreator 2015-03-22T22:24:18
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eSymQt
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    comment.cc \
    member.cc \
    mysqlquery.cc \
    util.cc \
    vote.cc \
    test.cpp \
    mysqlvote.cc \
    mysqlmember.cc \
    mysqlboard.cc

HEADERS  += mainwindow.h \
    comment.h \
    interface.h \
    member.h \
    mysqlquery.h \
    util.h \
    vote.h \
    test.h \
    mysqlvote.h \
    mysqlmember.h \
    mysqlboard.h

FORMS    += mainwindow.ui
