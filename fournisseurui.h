#ifndef FOURNISSEURUI_H
#define FOURNISSEURUI_H

#include <QDialog>
#include "fournisseur.h"
#include "chatgptclient.h"
namespace Ui {
class fournisseurUI;
}

class fournisseurUI : public QDialog
{
    Q_OBJECT

public:
    explicit fournisseurUI(QWidget *parent = nullptr);
    ~fournisseurUI();

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void on_add_clicked();

    void on_update_clicked();

    void on_deletebt_clicked();

    void on_pushButton_rech_clicked();

    void on_comboBox_tri_currentIndexChanged(int index);

    void on_pushButton_stat_clicked();

    void on_pushButton_pdf_clicked();

    void on_send_clicked();
private:

    bool ctr_saisie();
    void remplirChamps(const QString &ref);
    void clearFields();

    Ui::fournisseurUI *ui;
    fournisseur f;
    ChatGPTClient *client;

};

#endif // FOURNISSEURUI_H
