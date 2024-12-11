#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDebug>
#include <QDateTime> // For time functionality

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serialPort(new QSerialPort(this)) // Initialize QSerialPort
{
    ui->setupUi(this);

    // Initialize UI
    ui->accessGrantedLED->setStyleSheet("background-color: gray;"); // "Access Granted" LED off
    ui->statusLabel->setText("Waiting for Access...");

    // Initialize Serial Port
    initializeSerialPort();

    // Connect the serial port readyRead signal to the readFromArduino slot
    connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::readFromArduino);
}

MainWindow::~MainWindow()
{
    if (serialPort->isOpen()) {
        serialPort->close();
    }
    delete ui;
}

void MainWindow::initializeSerialPort()
{
    serialPort->setPortName("COM7"); // Set the correct port name (replace with your Arduino's port)
    serialPort->setBaudRate(QSerialPort::Baud115200); // Match the Arduino's baud rate
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (serialPort->open(QIODevice::ReadWrite)) {
        qDebug() << "Serial Port Opened Successfully.";
    } else {
        qDebug() << "Failed to Open Serial Port: " << serialPort->errorString();
    }
}

void MainWindow::on_startButton_clicked()
{
    if (serialPort->isOpen()) {
        serialPort->write("S"); // Send 'S' command to Arduino
        qDebug() << "Sent 'S' command to Arduino.";

        // Simulate access attempt for granted access
        QString user = "User1";  // Replace with actual user (e.g., from keypad input)
        QString code = "11";     // Replace with the actual code entered from the keypad

        // Simulate a correct code (Access Granted)
        bool isAccessGranted = true; // You can set this based on the actual code validation logic

        if (isAccessGranted) {
            ui->statusLabel->setText("Access Granted: Motor Running");
            ui->accessGrantedLED->setStyleSheet("background-color: green;"); // LED turns green

            // Record the granted access attempt
            recordAccessAttempt(user, code, "Granted");
        } else {
            ui->statusLabel->setText("Access Denied");
            ui->accessGrantedLED->setStyleSheet("background-color: red;"); // LED turns red

            // Record the denied access attempt
            recordAccessAttempt(user, code, "Denied");
        }

        // Reset UI after 10 seconds
        QTimer::singleShot(10000, this, [=]() {
            ui->statusLabel->setText("Waiting for Access...");
            ui->accessGrantedLED->setStyleSheet("background-color: gray;"); // LED off
        });
    } else {
        qDebug() << "Serial Port is not open!";
        ui->statusLabel->setText("Error: Serial Port not open");
    }
}

void MainWindow::recordAccessAttempt(const QString &user, const QString &code, const QString &accessStatus)
{
    // Get the current date and time
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    // Get the row count and add a new row in the table
    int rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowCount);

    // Add the data to the new row
    ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(currentTime)); // Time
    ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(user)); // User
    ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(code)); // Code
    ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(accessStatus)); // Access Status
}

void MainWindow::readFromArduino()
{
    QByteArray data = serialPort->readAll();  // Read all data from the serial port
    QString receivedData = QString::fromStdString(data.toStdString());

    // Debugging: Output received data
    qDebug() << "Received Data: " << receivedData;

    // Trim any leading or trailing whitespace/newline characters
    receivedData = receivedData.trimmed();

    // Remove any unexpected carriage returns or newlines within the data
    receivedData.replace("\r\n", " ");  // Replace newline characters with a space for better splitting

    // Split the data by commas to parse key-value pairs
    QStringList dataList = receivedData.split(",");

    // Debugging: Check if the list has the expected number of elements
    qDebug() << "Data List: " << dataList;

    // Ensure there are at least 2 elements (one for Code and one for Status)
    if (dataList.size() >= 2) {
        // Attempt to parse Code and Status
        QString code;
        QString status;

        // Extract Code (should be the first item)
        QString codeData = dataList[0].split(":").last().trimmed();
        if (!codeData.isEmpty()) {
            code = codeData;
        }

        // Extract Status (should be the second item)
        QString statusData = dataList[1].split(":").last().trimmed();
        if (!statusData.isEmpty()) {
            status = statusData;
        }

        // Generate current timestamp in Qt
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

        // Ensure that both Code and Status are parsed
        if (!code.isEmpty() && !status.isEmpty()) {
            // Now you can store this information in a QTableWidget or process it further
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(timestamp));  // Display the timestamp
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem("User1"));    // Add a user (this can be dynamic)
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(code));      // Display the code
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(status));    // Display the status
        } else {
            qDebug() << "Missing or invalid Code or Status.";
        }
    } else {
        // Handle the case where the data format is incorrect
        qDebug() << "Received data format is incorrect or incomplete.";
    }
}

