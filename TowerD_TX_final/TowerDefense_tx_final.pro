#-------------------------------------------------
#
# Project created by QtCreator 2013-08-22T22:46:33
#
#-------------------------------------------------

QT       += core gui multimedia

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TowerDefense
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    towerposition.cpp \
    tower.cpp \
    waypoint.cpp \
    enemy.cpp \
    bullet.cpp \
    audioplayer.cpp \
    plistreader.cpp \
    tlymcell.cpp \
    blymcell.cpp \
    enemyplus.cpp \
    enemyharmonway.cpp \
    enemydouble.cpp \
    hiv.cpp \
    hivplus.cpp \
    towerrangeall.cpp \
    towertunshi.cpp \
    bulleteat.cpp \
    tunshiplus.cpp \
    bulletslow.cpp \
    blymcellplus.cpp

HEADERS  += mainwindow.h \
    towerposition.h \
    tower.h \
    waypoint.h \
    utility.h \
    enemy.h \
    bullet.h \
    audioplayer.h \
    plistreader.h \
    tlymcell.h \
    blymcell.h \
    enemyplus.h \
    enemyharmonway.h \
    enemydouble.h \
    hiv.h \
    hivplus.h \
    towerrangeall.h \
    towertunshi.h \
    bulleteat.h \
    tunshiplus.h \
    bulletslow.h \
    blymcellplus.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
CONFIG+=resources_big
