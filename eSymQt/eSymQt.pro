#-------------------------------------------------
#
# Project created by QtCreator 2015-03-22T22:24:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eSymQt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    comment.cc \
    commentpopup.cc \
    conndata.cc \
    follow.cc \
    join.cc \
    main.cc \
    mainform.cc \
    member.cc \
    mysqlboard.cc \
    mysqlmember.cc \
    mysqlquery.cc \
    mysqlvote.cc \
    newbook.cc \
    util.cc \
    vote.cc \
    votepopup.cc

HEADERS  += mainwindow.h \
    comment.h \
    commentpopup.h \
    conndata.h \
    follow.hpp \
    interface.h \
    join.h \
    main.h \
    mainform.h \
    member.h \
    mysqlboard.h \
    mysqlmember.h \
    mysqlquery.h \
    mysqlvote.h \
    newbook.h \
    util.h \
    vote.h \
    votepopup.h

FORMS    += mainwindow.ui
