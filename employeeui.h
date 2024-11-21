#ifndef EMPLOYEEUI_H
#define EMPLOYEEUI_H

#include <QDialog>
#include <QMessageBox>

#include "fournisseur.h"

namespace Ui {
class employeeUI;
}

class employeeUI : public QDialog
{
    Q_OBJECT

public:
    explicit employeeUI(QWidget *parent = nullptr);
    ~employeeUI();

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void on_ajouter_clicked();

    void on_modifier_clicked();

    void on_del_clicked();

private:
    Ui::employeeUI *ui;
    employee e;
};

#endif // EMPLOYEEUI_H
