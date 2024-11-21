/********************************************************************************
** Form generated from reading UI file 'statistique.ui'
**
** Created by: Qt User Interface Compiler version 6.2.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATISTIQUE_H
#define UI_STATISTIQUE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_statistique
{
public:
    QPushButton *pushButton_11;
    QLabel *label_chat;

    void setupUi(QDialog *statistique)
    {
        if (statistique->objectName().isEmpty())
            statistique->setObjectName(QString::fromUtf8("statistique"));
        statistique->resize(874, 688);
        pushButton_11 = new QPushButton(statistique);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setGeometry(QRect(752, 647, 111, 31));
        pushButton_11->setStyleSheet(QString::fromUtf8(""));
        label_chat = new QLabel(statistique);
        label_chat->setObjectName(QString::fromUtf8("label_chat"));
        label_chat->setGeometry(QRect(10, 10, 850, 600));

        retranslateUi(statistique);

        QMetaObject::connectSlotsByName(statistique);
    } // setupUi

    void retranslateUi(QDialog *statistique)
    {
        statistique->setWindowTitle(QCoreApplication::translate("statistique", "Dialog", nullptr));
        pushButton_11->setText(QCoreApplication::translate("statistique", "Fermer", nullptr));
        label_chat->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class statistique: public Ui_statistique {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTIQUE_H
