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
QT += charts
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
    ../../Users/Asus/Downloads/add.png \
    ../../Users/Asus/Downloads/bulb.png \
    ../../Users/Asus/Downloads/delete.png \
    ../../Users/Asus/Downloads/edit-button.png \
    ../../Users/Asus/Downloads/envelope.png \
    ../../Users/Asus/Downloads/export.png \
    ../../Users/Asus/Downloads/idea.gif \
    ../../Users/Asus/Downloads/led-light.png \
    ../../Users/Asus/Downloads/man.png \
    ../../Users/Asus/Downloads/person.png \
    ../../Users/Asus/Downloads/pie-chart.png \
    ../../Users/Asus/Downloads/pour zoro.zip \
    ../../Users/Asus/Downloads/pour zoro.zip \
    ../../Users/Asus/Downloads/pour zoro.zip \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/11.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/11.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/11.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/Sal.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/Sal.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/Sal.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/abri (1).png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/abri (1).png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/abri (1).png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/abri.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/abri.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/abri.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/acc.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/acc.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/acc.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/acci.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/acci.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/acci.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/ajouter-un-bouton.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/ajouter-un-bouton.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/ajouter-un-bouton.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/bg.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/bg.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/bg.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/bgW.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/bgW.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/bgW.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/blue.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/blue.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/blue.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/bouton-retour.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/bouton-retour.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/bouton-retour.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/chercher.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/chercher.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/chercher.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/contact (1).png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/contact (1).png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/contact (1).png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/contact.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/contact.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/contact.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/courrier.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/courrier.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/courrier.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/crudbg.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/crudbg.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/crudbg.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/deconnexion (1).png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/deconnexion (1).png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/deconnexion (1).png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/deconnexion.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/deconnexion.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/deconnexion.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/diagramme-circulaire.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/diagramme-circulaire.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/diagramme-circulaire.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/emp.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/emp.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/emp.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/empCon.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/empCon.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/empCon.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/employes (2).png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/employes (2).png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/employes (2).png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/employes.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/employes.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/employes.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/fichier.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/fichier.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/fichier.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/filtre.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/filtre.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/filtre.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/importer-exporter.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/importer-exporter.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/importer-exporter.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/listEmp.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/listEmp.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/listEmp.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/livraison-rapide (1).png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/livraison-rapide (1).png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/livraison-rapide (1).png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/log.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/log.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/log.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/logB.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/logB.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/logB.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/logistics-delivery.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/logistics-delivery.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/logistics-delivery.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/logo.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/logo.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/logo.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/logoG.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/logoG.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/logoG.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/mettre-a-jour-les-fleches.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/mettre-a-jour-les-fleches.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/mettre-a-jour-les-fleches.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/picG.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/picG.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/picG.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/picP.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/picP.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/picP.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/rech.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/rech.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/rech.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/rechCon.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/rechCon.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/rechCon.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/rechhh.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/rechhh.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/rechhh.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/rechsal.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/rechsal.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/rechsal.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/stat.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/stat.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/stat.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/supprimer.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/supprimer.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/supprimer.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/undo.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/undo.png \
    ../../Users/Asus/Downloads/pour zoro/pour zoro/undo.png \
    ../../Users/Asus/Downloads/tool.png \
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
