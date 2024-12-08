#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSettings>  // For saving/loading preferences
#include <QApplication>
#include <QMainWindow>
#include "Employe.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool sendEmail(const QString &to, const QString &subject, const QString &body);
    //bool sendWelcomeEmail(const QString &toEmail, const QString &firstName, const QString &lastName, int cin);
private slots:
    void on_AddEmp_clicked();

    void on_employee_pushButton2_clicked();

    void on_employee_pushButton_clicked();

    void on_viewListe_clicked();

    void on_AddList_btn_clicked();

    void on_Uapdatelist_btn_clicked();

    void on_deletelist_btn_3_clicked();

    void on_deletelist_btn_clicked();

    void on_home_pushButton_3_clicked();

    void on_log_pushButton_2_clicked();

    void on_home_pushButton_2_clicked();

    void on_home_pushButton_4_clicked();

    void on_home_pushButton_5_clicked();

    void on_log_pushButton_clicked();

    void on_log_pushButton_3_clicked();

    void on_log_pushButton_4_clicked();

    void on_log_pushButton_5_clicked();

    void on_employee_pushButton_3_clicked();

    void on_employee_pushButton_4_clicked();

    void on_employee_pushButton_5_clicked();

    void on_Updatelist_btn2_clicked();

    void on_deletelist_btn_6_clicked();

    void on_refrech_clicked();

    void on_refrech_4_clicked();

    void on_Exportlist_btn_clicked();

    void on_Sort_btn_clicked();

    void goToPreviousPage();

    void searchInListEmp(const QString &searchText);

    void searchInListEmployee2(const QString &searchText);



    //void on_Home_currentChanged(int index);





    bool isNumeric(const QString &searchText);

    void on_pushButton_Login_clicked();



    //void on_AddList_btn_4_clicked();

    void on_refrech_Con_clicked();

    void on_stat_clicked();

    void on_deletelist_btn_7_clicked();

    void on_Uapdatelist_btn_4_clicked();

    void on_log_pushButton_8_clicked();

    void on_log_pushButton_9_clicked();

    void on_log_pushButton_10_clicked();

    void on_log_pushButton_11_clicked();


    void on_Exportlist_btn_2_clicked();




    void on_Sort_btn_2_clicked();
    void searchInListCong2(const QString &searchText);
    void searchInListCong(const QString &searchText);

    void on_refrech_conggg_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_14_clicked();

    void on_viewCong_clicked();

    void on_home_pushButton_6_clicked();

    void on_employee_pushButton_6_clicked();

    void on_employee_pushButton_2_clicked();





private:

    bool isAuthenticated = false; // Tracks whether the user is logged in
    void on_tabBarClicked(int index);
     bool handleLogin();

     void setupConnections();


    Ui::MainWindow *ui;
    Employe e;
};

#endif // MAINWINDOW_H
