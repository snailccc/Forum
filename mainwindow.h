#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "plate.h"
#include "user.h"
#include "loginview.h"
#include "ui_appoint.h"
#include<QMainWindow>
#include<QGridLayout>
#include<QPushButton>
#include<QWidget>
#include<QToolBar>
#include<QAction>
#include<QApplication>
#include<QUrl>
#include<QVariant>
#include<QTextCodec>

namespace Ui {
class MainWindow;
class appoint;
}
class MainWindow;
class AppointView;
/////////////////AppointView///////////////////////////////
class AppointView:public QDialog
{
    Q_OBJECT
private:
    Ui::appoint *ui;
    QString userId, plateId;
public:
    AppointView(int type=0, QWidget *parent=0);
//    void Appointing();
//    void Removing();
    QString UserId();
    QString PlateId();
private slots:
    void on_buttonBox_accepted();
};

/////////////////MainWindow///////////////////////////////
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QGridLayout *layout;
    vector<Plate*> plates;
    QWidget *background;
    QToolBar *toolbar;
    QAction *logout,*exit,*account_info,*appoint,*remove;
    Ui::MainWindow *ui;
    AppointView *manager_View;

public:
    explicit MainWindow(QWidget *parent=0);
    friend vector<Plate*>& operator <<(vector<Plate*>& plateGroup, QSqlDatabase db);
    void Initial_Background();
    void Change_Background(int old_type);
    void Initial_Action();
    ~MainWindow();
protected slots:
    void Create_Plate_View();
    void Logout();
    void Get_Account_Info();
    void Appointing();
    void Removing();
};

#endif // MAINWINDOW_H
