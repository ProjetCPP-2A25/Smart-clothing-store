#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QPropertyAnimation> // Inclusion pour l'animation
#include <QScreen>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Connection c;
    bool test = c.createconnect();

    if (test)
    {
        // Configuration de l'animation pour le plein écran
        QPropertyAnimation *animation = new QPropertyAnimation(&w, "geometry");
        animation->setDuration(1000); // Durée en millisecondes (1 seconde)

        // Obtenir les dimensions de l'écran
        QRect screenGeometry = QApplication::primaryScreen()->geometry();
        QRect startRect(screenGeometry.width() / 2, screenGeometry.height() / 2, 0, 0); // Position initiale réduite
        QRect endRect = screenGeometry; // Plein écran

        animation->setStartValue(startRect); // Valeurs de départ
        animation->setEndValue(endRect);     // Valeurs finales
        animation->setEasingCurve(QEasingCurve::OutQuad); // Effet d'animation fluide

        w.show();             // Affiche la fenêtre
        animation->start();   // Démarre l'animation

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                              QObject::tr("connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

    return a.exec();
}
