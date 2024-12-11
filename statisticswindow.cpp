#include "statisticswindow.h"
#include "ui_statisticswindow.h"
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QSqlQuery>
#include <QVBoxLayout>

StatisticsWindow::StatisticsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatisticsWindow),
    chartView(new QChartView()) // Ensure this matches the case
{
    ui->setupUi(this);

    // Create a layout to hold the chart view
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(chartView);  // Add the chart view to the layout
    setLayout(layout);

    // Set window properties
    setWindowTitle("Employee Leave Status");
    setFixedSize(500, 400);  // Resize the window to be smaller

    // Call the method to show employee statistics
    showEmployeeStatistics();
}

StatisticsWindow::~StatisticsWindow()
{
    delete ui;
    delete chartView;  // Don't forget to delete the chartView to free resources
}

void StatisticsWindow::showEmployeeStatistics()
{
    // Query total number of employees
    QSqlQuery queryTotal("SELECT COUNT(*) AS total_count FROM EMPLOYEE");
    int totalEmployees = 0;
    if (queryTotal.next()) {
        totalEmployees = queryTotal.value("total_count").toInt();
    }

    // Query active employees
    QSqlQuery queryActive(
        "SELECT COUNT(*) AS active_count "
        "FROM EMPLOYEE "
        "WHERE FIRST_DAY_OF_LEAVE IS NULL "
        "   OR LAST_DAY_OF_LEAVE IS NULL "
        "   OR DATE('now') NOT BETWEEN FIRST_DAY_OF_LEAVE AND LAST_DAY_OF_LEAVE");
    int activeEmployees = 0;
    if (queryActive.next()) {
        activeEmployees = queryActive.value("active_count").toInt();
    }

    // Calculate employees on leave
    int onLeaveEmployees = totalEmployees - activeEmployees;

    // Create a pie chart
    QPieSeries *series = new QPieSeries();
    series->append("Active (Not on Leave)", activeEmployees);
    series->append("On Leave", onLeaveEmployees);

    // Set percentage labels for the slices
    for (QPieSlice *slice : series->slices()) {
        if (totalEmployees > 0) {
            double percentage = (slice->value() / totalEmployees) * 100;
            slice->setLabel(QString("%1: %2%").arg(slice->label()).arg(QString::number(percentage, 'f', 1))); // One decimal place
        } else {
            slice->setLabel(QString("%1: 0%").arg(slice->label())); // Handle case with no employees
        }
    }

    // Explode and label the first slice (Active employees)
    if (!series->slices().isEmpty()) {
        QPieSlice *highlighted = series->slices().at(0);
        highlighted->setExploded(true);
        highlighted->setLabelVisible(true);
    }

    // Create chart and set its properties
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Employee Leave Status");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Set the chart in the chart view
    chartView->setChart(chart);
}
