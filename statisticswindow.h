#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include <QDialog>
#include <QtCharts/QChartView>  // Include QChartView
#include <QtCharts/QPieSeries>  // Include QPieSeries
#include <QtCharts/QPieSlice>   // Include QPieSlice for the slice manipulation

namespace Ui {
class StatisticsWindow;
}

class StatisticsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StatisticsWindow(QWidget *parent = nullptr);
    ~StatisticsWindow();

    void showEmployeeStatistics();

private:
    Ui::StatisticsWindow *ui;
    QChartView *chartView;  // Declare chartView here as a member variable
};

#endif // STATISTICSWINDOW_H
