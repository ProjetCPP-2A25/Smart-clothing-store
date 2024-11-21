#include "statistique.h"
#include "ui_statistique.h"

#include "fournisseur.h"

#include <QPainter>
#include <QPaintEvent>


statistique::statistique(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistique)
{
    ui->setupUi(this);
}
void statistique::paintEvent(QPaintEvent *)
{

    int A= F.statistique1(); // a = 30 ( nb de quantité inf 30 )
    int B= F.statistique2(); // b = 50 ( nb de quantité sup 30 )
    float s1= A*100 ; // s1 = 3000  a = 30
    float s2=B*100;  // s2 = 5000  b = 50
    float nb = A+B; // nb = 80
    float q2 ;
    q2 = s1/nb ;   // q2 = 3000/80 = 37.5 %
    float q3;
    q3=s2/nb;      // q3 = 5000/80 = 62.5 %
    float y  ;
    y = (q2*360)/100 ;  // y = 37.5*360/100 = 135
    float m;
    m= (q3*360)/100;   // m = 62.5*360/100 = 225

    float res1 = 16*y;  // res1  = 2160
    float res2 = 16*m;  // res2 = 3600

    QChartView *chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);

    QPieSeries *series = new QPieSeries();
    series->append("Adresse Tunis", res1);

    series->append("Adresse étranger", res2);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistique par rapport l'adresse");

    chartView = new QChartView(chart,ui->label_chat);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(850,600);
    chartView->show();
}
statistique::~statistique()
{
    delete ui;
}


void statistique::on_pushButton_11_clicked()
{
    close();
}

