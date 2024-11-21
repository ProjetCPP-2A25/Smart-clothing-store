#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------
QT += core gui network


QT += core gui sql
QT+=sql
QT += serialport
QT += network
QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atelier_Connexion
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

SOURCES += \
    arduino.cpp \
    livraison.cpp \
        main.cpp \
        mainwindow.cpp \
    connection.cpp

HEADERS += \
    arduino.h \
    livraison.h \
        mainwindow.h \
    connection.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc

DISTFILES += \
    pour youssef/Sal.png \
    pour youssef/abri (1).png \
    pour youssef/abri.png \
    pour youssef/acc.png \
    pour youssef/acci.png \
    pour youssef/bg.png \
    pour youssef/bgW.png \
    pour youssef/contact.png \
    pour youssef/courrier.png \
    pour youssef/deconnexion (1).png \
    pour youssef/deconnexion.png \
    pour youssef/emp.png \
    pour youssef/empCon.png \
    pour youssef/employes (2).png \
    pour youssef/employes.png \
    pour youssef/listEmp.png \
    pour youssef/livraison-rapide (1).png \
    pour youssef/logB.png \
    pour youssef/logistics-delivery.png \
    pour youssef/logo.png \
    pour youssef/logoG.png \
    pour youssef/picP.png \
    pour youssef/rech.png \
    pour youssef/rechCon.png \
    pour youssef/rechsal.png \
    pour youssef/stat.png \
    pour youssef/undo.png
