#include "StatsWindow.h"
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

StatsWindow::StatsWindow(QWidget *parent) :
    QWidget(parent),
{
    ui->setupUi(this);  // Charger l'UI générée par Qt Designer

    // Connecter le bouton "Fermer" au slot
    connect(ui->closeButton, &QPushButton::clicked, this, &StatsWindow::fermerFenetre);

    // Initialiser le graphique (par exemple)
    graphicsView = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    graphicsView->setScene(scene);
}

StatsWindow::~StatsWindow()
{
    delete ui;  // Libérer la mémoire de l'interface
}

void StatsWindow::afficherHistogramme(int effectuees, int enRetard)
{
    scene->clear();  // Effacer la scène existante

    // Calcul des dimensions des barres
    int barWidth = 100;
    int maxHeight = 200;
    int total = effectuees + enRetard;

    if (total == 0) return;

    int heightEffectuees = (effectuees * maxHeight) / total;
    int heightEnRetard = (enRetard * maxHeight) / total;

    // Dessiner les barres pour l'histogramme
    scene->addRect(50, maxHeight - heightEffectuees, barWidth, heightEffectuees, QPen(Qt::black), QBrush(Qt::green));
    scene->addRect(200, maxHeight - heightEnRetard, barWidth, heightEnRetard, QPen(Qt::black), QBrush(Qt::red));

    // Ajouter les étiquettes
    scene->addText("Effectuées")->setPos(50, maxHeight + 10);
    scene->addText("En retard")->setPos(200, maxHeight + 10);
}

// Slot pour fermer la fenêtre
void StatsWindow::fermerFenetre()
{
    this->close();  // Ferme la fenêtre des statistiques
}
