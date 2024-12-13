#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       += core gui sql
QT += printsupport
QT += network
QT += serialport
QT += network
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
    Employe.cpp \
    arduino.cpp \
    client.cpp \
    livraison.cpp \
        main.cpp \
        mainwindow.cpp \
    connection.cpp

HEADERS += \
    Employe.h \
    arduino.h \
    client.h \
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
    test.qrc
QT += core gui charts

DISTFILES += \
    ../../../Downloads/pour zoro/pour zoro/11.png \
    ../../../Downloads/pour zoro/pour zoro/Sal.png \
    ../../../Downloads/pour zoro/pour zoro/abri (1).png \
    ../../../Downloads/pour zoro/pour zoro/abri.png \
    ../../../Downloads/pour zoro/pour zoro/acc.png \
    ../../../Downloads/pour zoro/pour zoro/acci.png \
    ../../../Downloads/pour zoro/pour zoro/ajouter-un-bouton.png \
    ../../../Downloads/pour zoro/pour zoro/bg.png \
    ../../../Downloads/pour zoro/pour zoro/bgW.png \
    ../../../Downloads/pour zoro/pour zoro/blue.png \
    ../../../Downloads/pour zoro/pour zoro/bouton-retour.png \
    ../../../Downloads/pour zoro/pour zoro/chercher.png \
    ../../../Downloads/pour zoro/pour zoro/contact (1).png \
    ../../../Downloads/pour zoro/pour zoro/contact.png \
    ../../../Downloads/pour zoro/pour zoro/courrier.png \
    ../../../Downloads/pour zoro/pour zoro/crudbg.png \
    ../../../Downloads/pour zoro/pour zoro/deconnexion (1).png \
    ../../../Downloads/pour zoro/pour zoro/deconnexion.png \
    ../../../Downloads/pour zoro/pour zoro/diagramme-circulaire.png \
    ../../../Downloads/pour zoro/pour zoro/emp.png \
    ../../../Downloads/pour zoro/pour zoro/empCon.png \
    ../../../Downloads/pour zoro/pour zoro/employes (2).png \
    ../../../Downloads/pour zoro/pour zoro/employes.png \
    ../../../Downloads/pour zoro/pour zoro/fichier.png \
    ../../../Downloads/pour zoro/pour zoro/filtre.png \
    ../../../Downloads/pour zoro/pour zoro/importer-exporter.png \
    ../../../Downloads/pour zoro/pour zoro/listEmp.png \
    ../../../Downloads/pour zoro/pour zoro/livraison-rapide (1).png \
    ../../../Downloads/pour zoro/pour zoro/log.png \
    ../../../Downloads/pour zoro/pour zoro/logB.png \
    ../../../Downloads/pour zoro/pour zoro/logistics-delivery.png \
    ../../../Downloads/pour zoro/pour zoro/logo.png \
    ../../../Downloads/pour zoro/pour zoro/logoG.png \
    ../../../Downloads/pour zoro/pour zoro/mettre-a-jour-les-fleches.png \
    ../../../Downloads/pour zoro/pour zoro/picG.png \
    ../../../Downloads/pour zoro/pour zoro/picP.png \
    ../../../Downloads/pour zoro/pour zoro/rech.png \
    ../../../Downloads/pour zoro/pour zoro/rechCon.png \
    ../../../Downloads/pour zoro/pour zoro/rechhh.png \
    ../../../Downloads/pour zoro/pour zoro/rechsal.png \
    ../../../Downloads/pour zoro/pour zoro/stat.png \
    ../../../Downloads/pour zoro/pour zoro/supprimer.png \
    ../../../Downloads/pour zoro/pour zoro/undo.png \
    img/contact (1).png
