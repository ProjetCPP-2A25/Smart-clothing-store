#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QString>
#include <QTableWidgetItem>
#include <QDateTime> // For getting the current date/time

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked(); // Slot for Start Button
    void recordAccessAttempt(const QString &user, const QString &code, const QString &accessStatus); // Slot to record data
    void readFromArduino();


private:
    Ui::MainWindow *ui;
    QSerialPort *serialPort;  // Serial port object for communication with Arduino
    void initializeSerialPort(); // Method to initialize serial communication
    void keypadInputHandler();


};

#endif // MAINWINDOW_H
