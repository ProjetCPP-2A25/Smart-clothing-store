/********************************************************************************
** Form generated from reading UI file 'fournisseurui.ui'
**
** Created by: Qt User Interface Compiler version 6.2.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FOURNISSEURUI_H
#define UI_FOURNISSEURUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_fournisseurUI
{
public:
    QLabel *label_8;
    QLabel *label_4;
    QLabel *label_11;
    QPushButton *deletebt;
    QLineEdit *ID;
    QLabel *label_10;
    QLabel *label;
    QLineEdit *CONTACT;
    QLabel *label_3;
    QLineEdit *IDS;
    QLineEdit *NAME;
    QPushButton *update;
    QLineEdit *EMAIL;
    QLabel *label_9;
    QLabel *label_6;
    QLabel *label_2;
    QLabel *label_5;
    QPushButton *add;
    QLabel *label_7;
    QLineEdit *ADRESSE;
    QLineEdit *TELEPHONE;
    QTableView *tableView;
    QLabel *label_12;
    QLabel *label_14;
    QComboBox *comboBox_rech;
    QLineEdit *lineEdit_rech;
    QPushButton *pushButton_rech;
    QPushButton *pushButton_stat;
    QComboBox *comboBox_tri;
    QLineEdit *lineEdit_pdf;
    QPushButton *pushButton_pdf;

    void setupUi(QDialog *fournisseurUI)
    {
        if (fournisseurUI->objectName().isEmpty())
            fournisseurUI->setObjectName(QString::fromUtf8("fournisseurUI"));
        fournisseurUI->resize(965, 601);
        label_8 = new QLabel(fournisseurUI);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(860, 80, 71, 20));
        label_4 = new QLabel(fournisseurUI);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(0, 0, 941, 581));
        label_4->setPixmap(QPixmap(QString::fromUtf8("../../../../pour youssef/bg.png")));
        label_4->setScaledContents(true);
        label_11 = new QLabel(fournisseurUI);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(750, 230, 63, 20));
        deletebt = new QPushButton(fournisseurUI);
        deletebt->setObjectName(QString::fromUtf8("deletebt"));
        deletebt->setGeometry(QRect(610, 300, 93, 29));
        ID = new QLineEdit(fournisseurUI);
        ID->setObjectName(QString::fromUtf8("ID"));
        ID->setGeometry(QRect(840, 250, 113, 26));
        label_10 = new QLabel(fournisseurUI);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 520, 61, 51));
        label_10->setPixmap(QPixmap(QString::fromUtf8("../../../../pour youssef/undo.png")));
        label_10->setScaledContents(true);
        label = new QLabel(fournisseurUI);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(820, 20, 141, 91));
        label->setPixmap(QPixmap(QString::fromUtf8("../../../../pour youssef/logo.png")));
        label->setScaledContents(true);
        CONTACT = new QLineEdit(fournisseurUI);
        CONTACT->setObjectName(QString::fromUtf8("CONTACT"));
        CONTACT->setGeometry(QRect(720, 250, 113, 26));
        label_3 = new QLabel(fournisseurUI);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(880, 230, 63, 20));
        IDS = new QLineEdit(fournisseurUI);
        IDS->setObjectName(QString::fromUtf8("IDS"));
        IDS->setGeometry(QRect(600, 250, 113, 26));
        NAME = new QLineEdit(fournisseurUI);
        NAME->setObjectName(QString::fromUtf8("NAME"));
        NAME->setGeometry(QRect(720, 170, 113, 26));
        update = new QPushButton(fournisseurUI);
        update->setObjectName(QString::fromUtf8("update"));
        update->setGeometry(QRect(850, 300, 93, 29));
        EMAIL = new QLineEdit(fournisseurUI);
        EMAIL->setObjectName(QString::fromUtf8("EMAIL"));
        EMAIL->setGeometry(QRect(720, 110, 113, 26));
        label_9 = new QLabel(fournisseurUI);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 20, 71, 61));
        label_9->setPixmap(QPixmap(QString::fromUtf8("../../../../pour youssef/abri (1).png")));
        label_9->setScaledContents(true);
        label_6 = new QLabel(fournisseurUI);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(870, 150, 63, 20));
        label_2 = new QLabel(fournisseurUI);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(160, 30, 771, 461));
        label_2->setPixmap(QPixmap(QString::fromUtf8("../../../../pour youssef/bgW.png")));
        label_2->setScaledContents(true);
        label_5 = new QLabel(fournisseurUI);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(750, 150, 63, 20));
        add = new QPushButton(fournisseurUI);
        add->setObjectName(QString::fromUtf8("add"));
        add->setGeometry(QRect(730, 300, 93, 29));
        label_7 = new QLabel(fournisseurUI);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(740, 80, 63, 20));
        ADRESSE = new QLineEdit(fournisseurUI);
        ADRESSE->setObjectName(QString::fromUtf8("ADRESSE"));
        ADRESSE->setGeometry(QRect(840, 170, 113, 26));
        TELEPHONE = new QLineEdit(fournisseurUI);
        TELEPHONE->setObjectName(QString::fromUtf8("TELEPHONE"));
        TELEPHONE->setGeometry(QRect(840, 110, 113, 26));
        tableView = new QTableView(fournisseurUI);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(520, 340, 441, 261));
        label_12 = new QLabel(fournisseurUI);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(-20, 0, 991, 601));
        label_12->setPixmap(QPixmap(QString::fromUtf8("../pour youssef/bg.png")));
        label_12->setScaledContents(true);
        label_14 = new QLabel(fournisseurUI);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(620, 230, 63, 20));
        comboBox_rech = new QComboBox(fournisseurUI);
        comboBox_rech->addItem(QString());
        comboBox_rech->addItem(QString());
        comboBox_rech->addItem(QString());
        comboBox_rech->setObjectName(QString::fromUtf8("comboBox_rech"));
        comboBox_rech->setGeometry(QRect(4, 50, 121, 24));
        lineEdit_rech = new QLineEdit(fournisseurUI);
        lineEdit_rech->setObjectName(QString::fromUtf8("lineEdit_rech"));
        lineEdit_rech->setGeometry(QRect(130, 50, 113, 24));
        pushButton_rech = new QPushButton(fournisseurUI);
        pushButton_rech->setObjectName(QString::fromUtf8("pushButton_rech"));
        pushButton_rech->setGeometry(QRect(250, 50, 80, 24));
        pushButton_stat = new QPushButton(fournisseurUI);
        pushButton_stat->setObjectName(QString::fromUtf8("pushButton_stat"));
        pushButton_stat->setGeometry(QRect(10, 110, 80, 24));
        comboBox_tri = new QComboBox(fournisseurUI);
        comboBox_tri->addItem(QString());
        comboBox_tri->addItem(QString());
        comboBox_tri->addItem(QString());
        comboBox_tri->addItem(QString());
        comboBox_tri->addItem(QString());
        comboBox_tri->addItem(QString());
        comboBox_tri->setObjectName(QString::fromUtf8("comboBox_tri"));
        comboBox_tri->setGeometry(QRect(10, 80, 271, 24));
        lineEdit_pdf = new QLineEdit(fournisseurUI);
        lineEdit_pdf->setObjectName(QString::fromUtf8("lineEdit_pdf"));
        lineEdit_pdf->setGeometry(QRect(100, 110, 113, 24));
        pushButton_pdf = new QPushButton(fournisseurUI);
        pushButton_pdf->setObjectName(QString::fromUtf8("pushButton_pdf"));
        pushButton_pdf->setGeometry(QRect(220, 111, 51, 24));
        label_4->raise();
        label_12->raise();
        label_2->raise();
        label_8->raise();
        label_11->raise();
        deletebt->raise();
        ID->raise();
        label_10->raise();
        label->raise();
        CONTACT->raise();
        label_3->raise();
        IDS->raise();
        NAME->raise();
        update->raise();
        EMAIL->raise();
        label_9->raise();
        label_6->raise();
        label_5->raise();
        add->raise();
        label_7->raise();
        ADRESSE->raise();
        TELEPHONE->raise();
        tableView->raise();
        label_14->raise();
        comboBox_rech->raise();
        lineEdit_rech->raise();
        pushButton_rech->raise();
        pushButton_stat->raise();
        comboBox_tri->raise();
        lineEdit_pdf->raise();
        pushButton_pdf->raise();

        retranslateUi(fournisseurUI);

        QMetaObject::connectSlotsByName(fournisseurUI);
    } // setupUi

    void retranslateUi(QDialog *fournisseurUI)
    {
        fournisseurUI->setWindowTitle(QCoreApplication::translate("fournisseurUI", "Dialog", nullptr));
        label_8->setText(QCoreApplication::translate("fournisseurUI", "Telephone", nullptr));
        label_4->setText(QString());
        label_11->setText(QCoreApplication::translate("fournisseurUI", "Contact", nullptr));
        deletebt->setText(QCoreApplication::translate("fournisseurUI", "Delete", nullptr));
        ID->setText(QString());
        label_10->setText(QString());
        label->setText(QString());
        CONTACT->setText(QString());
        label_3->setText(QCoreApplication::translate("fournisseurUI", "ID", nullptr));
        NAME->setText(QString());
        update->setText(QCoreApplication::translate("fournisseurUI", "Update", nullptr));
        label_9->setText(QString());
        label_6->setText(QCoreApplication::translate("fournisseurUI", "Adresse", nullptr));
        label_2->setText(QString());
        label_5->setText(QCoreApplication::translate("fournisseurUI", "Name", nullptr));
        add->setText(QCoreApplication::translate("fournisseurUI", "Add", nullptr));
        label_7->setText(QCoreApplication::translate("fournisseurUI", "Email", nullptr));
        label_12->setText(QString());
        label_14->setText(QCoreApplication::translate("fournisseurUI", "Delete", nullptr));
        comboBox_rech->setItemText(0, QCoreApplication::translate("fournisseurUI", "Nom", nullptr));
        comboBox_rech->setItemText(1, QCoreApplication::translate("fournisseurUI", "Adresse", nullptr));
        comboBox_rech->setItemText(2, QCoreApplication::translate("fournisseurUI", "Email", nullptr));

        pushButton_rech->setText(QCoreApplication::translate("fournisseurUI", "Recherche", nullptr));
        pushButton_stat->setText(QCoreApplication::translate("fournisseurUI", "Statistique", nullptr));
        comboBox_tri->setItemText(0, QCoreApplication::translate("fournisseurUI", "id croissants", nullptr));
        comboBox_tri->setItemText(1, QCoreApplication::translate("fournisseurUI", "id decroissants", nullptr));
        comboBox_tri->setItemText(2, QCoreApplication::translate("fournisseurUI", "nom decroissants", nullptr));
        comboBox_tri->setItemText(3, QCoreApplication::translate("fournisseurUI", "nom croissants", nullptr));
        comboBox_tri->setItemText(4, QCoreApplication::translate("fournisseurUI", "contact decroissants", nullptr));
        comboBox_tri->setItemText(5, QCoreApplication::translate("fournisseurUI", "contact croissants", nullptr));

        pushButton_pdf->setText(QCoreApplication::translate("fournisseurUI", "PDF", nullptr));
    } // retranslateUi

};

namespace Ui {
    class fournisseurUI: public Ui_fournisseurUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FOURNISSEURUI_H
