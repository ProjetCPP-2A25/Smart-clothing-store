/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_4;
    QPushButton *pushButton_8;
    QTableWidget *tableWidget_2;
    QLabel *label_4;
    QLabel *label_5;
    QListWidget *listWidget;
    QListWidget *listWidget_2;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_9;
    QLabel *label_10;
    QWidget *tab_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_adresse;
    QDateEdit *dateEdit_dateeffectuee;
    QDateEdit *dateEdit_dateprevue;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(953, 545);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 951, 481));
        tab = new QWidget();
        tab->setObjectName("tab");
        label = new QLabel(tab);
        label->setObjectName("label");
        label->setGeometry(QRect(-80, -10, 1021, 461));
        label->setPixmap(QPixmap(QString::fromUtf8(":/pour youssef/bg.png")));
        label->setScaledContents(true);
        label_3 = new QLabel(tab);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(150, 10, 781, 431));
        label_3->setAutoFillBackground(false);
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/pour youssef/bgW.png")));
        label_3->setScaledContents(true);
        label_3->setMargin(0);
        label_2 = new QLabel(tab);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(50, 0, 81, 81));
        label_2->setStyleSheet(QString::fromUtf8("  color: #000000; /* Text color */\n"
"  font-size: 14px; /* Font size */\n"
"  font-family: Arial, sans-serif; /* Font family */\n"
"  padding: 5px; "));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/pour youssef/logo.png")));
        label_2->setScaledContents(true);
        label_2->setWordWrap(false);
        label_2->setMargin(0);
        pushButton_5 = new QPushButton(tab);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(-10, 170, 161, 41));
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: transparent; /* Transparent background */\n"
"  color: #333333; /* Dark text color */\n"
"  border: none; /* No border */\n"
"  border-radius: 5px; /* Rounded corners */\n"
"  padding: 10px 20px; /* Padding inside the button */\n"
"  font-size: 11px; /* Font size */\n"
"  font-family: Arial, sans-serif; /* Font family */\n"
"font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgba(204, 204, 204, 0.2); /* Light grey tint on hover */\n"
"}\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/pour youssef/contact.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_5->setIcon(icon);
        pushButton_5->setIconSize(QSize(60, 35));
        pushButton = new QPushButton(tab);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(-20, 390, 90, 36));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: transparent; /* Transparent background */\n"
"  color: #333333; /* Dark text color */\n"
"  border: none; /* No border */\n"
"  border-radius: 5px; /* Rounded corners */\n"
"  padding: 10px 20px; /* Padding inside the button */\n"
"  font-size: 14px; /* Font size */\n"
"  font-family: Arial, sans-serif; /* Font family */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgba(204, 204, 204, 0.2); /* Light grey tint on hover */\n"
"}\n"
""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/pour youssef/deconnexion.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon1);
        pushButton->setIconSize(QSize(20, 20));
        pushButton_2 = new QPushButton(tab);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(-50, 290, 231, 51));
        pushButton_2->setAutoFillBackground(false);
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: transparent; /* Transparent background */\n"
"  color: #333333; /* Dark text color */\n"
"  border: none; /* No border */\n"
"  border-radius: 5px; /* Rounded corners */\n"
"  padding: 10px 20px; /* Padding inside the button */\n"
"  font-size: 11px; /* Font size */\n"
"  font-family: Arial, sans-serif; /* Font family */\n"
"font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgba(204, 204, 204, 0.2); /* Light grey tint on hover */\n"
"}\n"
""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/pour youssef/courrier.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon2);
        pushButton_2->setIconSize(QSize(60, 40));
        pushButton_3 = new QPushButton(tab);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(-20, 250, 171, 51));
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: transparent; /* Transparent background */\n"
"  color: #333333; /* Dark text color */\n"
"  border: none; /* No border */\n"
"  border-radius: 5px; /* Rounded corners */\n"
"  padding: 10px 20px; /* Padding inside the button */\n"
"  font-size: 11px; /* Font size */\n"
"  font-family: Arial, sans-serif; /* Font family */\n"
"font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgba(204, 204, 204, 0.2); /* Light grey tint on hover */\n"
"}\n"
""));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/pour youssef/logistics-delivery.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_3->setIcon(icon3);
        pushButton_3->setIconSize(QSize(60, 40));
        pushButton_6 = new QPushButton(tab);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(-10, 130, 181, 41));
        pushButton_6->setMinimumSize(QSize(0, 0));
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: transparent; /* Transparent background */\n"
"  color: #333333; /* Dark text color */\n"
"  border: none; /* No border */\n"
"  border-radius: 5px; /* Rounded corners */\n"
"  padding: 10px 20px; /* Padding inside the button */\n"
"  font-size: 11px; /* Font size */\n"
"  font-family: Arial, sans-serif; /* Font family */\n"
"font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgba(204, 204, 204, 0.2); /* Light grey tint on hover */\n"
"}\n"
""));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/pour youssef/employes.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_6->setIcon(icon4);
        pushButton_6->setIconSize(QSize(60, 35));
        pushButton_7 = new QPushButton(tab);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(-20, 90, 150, 40));
        pushButton_7->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: transparent; /* Transparent background */\n"
"  color: #333333; /* Dark text color */\n"
"  border: none; /* No border */\n"
"  border-radius: 5px; /* Rounded corners */\n"
"  padding: 10px 20px; /* Padding inside the button */\n"
"  font-size: 11px; /* Font size */\n"
"  font-family: Arial, sans-serif; /* Font family */\n"
"font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgba(204, 204, 204, 0.2); /* Light grey tint on hover */\n"
"}\n"
""));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/pour youssef/abri (1).png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_7->setIcon(icon5);
        pushButton_7->setIconSize(QSize(60, 35));
        pushButton_4 = new QPushButton(tab);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(-10, 210, 181, 41));
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: transparent; /* Transparent background */\n"
"  color: #333333; /* Dark text color */\n"
"  border: none; /* No border */\n"
"  border-radius: 5px; /* Rounded corners */\n"
"  padding: 10px 20px; /* Padding inside the button */\n"
"  font-size: 11px; /* Font size */\n"
"  font-family: Arial, sans-serif; /* Font family */\n"
"font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgba(204, 204, 204, 0.2); /* Light grey tint on hover */\n"
"}\n"
""));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/pour youssef/livraison-rapide (1).png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_4->setIcon(icon6);
        pushButton_4->setIconSize(QSize(60, 35));
        pushButton_8 = new QPushButton(tab);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(750, 20, 181, 41));
        pushButton_8->setBaseSize(QSize(0, 0));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        pushButton_8->setFont(font);
        pushButton_8->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: transparent; /* Transparent background */\n"
"  color: #333333; /* Dark text color */\n"
"  border: none; /* No border */\n"
"  border-radius: 5px; /* Rounded corners */\n"
"  padding: 10px 20px; /* Padding inside the button */\n"
"  font-size: 13px; /* Font size */\n"
"  font-family: Arial, sans-serif; /* Font family */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgba(204, 204, 204, 0.2); /* Light grey tint on hover */\n"
"}\n"
""));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/pour youssef/picP.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_8->setIcon(icon7);
        pushButton_8->setIconSize(QSize(60, 35));
        tableWidget_2 = new QTableWidget(tab);
        if (tableWidget_2->columnCount() < 5)
            tableWidget_2->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QFont font1;
        font1.setPointSize(7);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font1);
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget_2->setObjectName("tableWidget_2");
        tableWidget_2->setGeometry(QRect(410, 330, 511, 101));
        tableWidget_2->setTabletTracking(false);
        tableWidget_2->setFocusPolicy(Qt::FocusPolicy::TabFocus);
        tableWidget_2->setColumnCount(5);
        label_4 = new QLabel(tab);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(610, 40, 191, 81));
        label_4->setScaledContents(true);
        label_5 = new QLabel(tab);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(590, 250, 191, 81));
        label_5->setScaledContents(true);
        listWidget = new QListWidget(tab);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(160, 100, 221, 141));
        listWidget_2 = new QListWidget(tab);
        listWidget_2->setObjectName("listWidget_2");
        listWidget_2->setGeometry(QRect(160, 280, 221, 141));
        label_6 = new QLabel(tab);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(180, 40, 191, 81));
        label_6->setScaledContents(true);
        label_7 = new QLabel(tab);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(160, 220, 251, 81));
        label_7->setScaledContents(true);
        label_9 = new QLabel(tab);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(530, 100, 401, 181));
        label_9->setPixmap(QPixmap(QString::fromUtf8(":/pour youssef/Sal.png")));
        label_9->setScaledContents(true);
        label_10 = new QLabel(tab);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(550, 110, 351, 51));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        lineEdit = new QLineEdit(tab_2);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(300, 200, 113, 24));
        lineEdit_adresse = new QLineEdit(tab_2);
        lineEdit_adresse->setObjectName("lineEdit_adresse");
        lineEdit_adresse->setGeometry(QRect(90, 280, 113, 24));
        dateEdit_dateeffectuee = new QDateEdit(tab_2);
        dateEdit_dateeffectuee->setObjectName("dateEdit_dateeffectuee");
        dateEdit_dateeffectuee->setGeometry(QRect(400, 50, 110, 25));
        dateEdit_dateprevue = new QDateEdit(tab_2);
        dateEdit_dateprevue->setObjectName("dateEdit_dateprevue");
        dateEdit_dateprevue->setGeometry(QRect(130, 90, 110, 25));
        tabWidget->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 953, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestion des Clients", nullptr));
        label->setText(QString());
        label_3->setText(QString());
        label_2->setText(QString());
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "  Gestion Client ", nullptr));
        pushButton->setText(QString());
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "   Gestion\n"
" Fournisseur", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Gestion Stock ", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "  Gestion Employe ", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "   Acceuil", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "  Gestion Livraison ", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Hi,Rabie", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "ID_Livreur", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Date_Effectuer", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Date prevue", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_2->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Adresse", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">Listes Des Livreurs</span></p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">Listes Des Livraison</span></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">Statut Livreurs</span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700;\">Calendrier Des Livraisons</span></p></body></html>", nullptr));
        label_9->setText(QString());
        label_10->setText(QCoreApplication::translate("MainWindow", "ID             NOM&PRENOM        Numero de telephone          Statut", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        lineEdit_adresse->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
