#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "plate.h"
#include "header.h"
#include "user.h"
#include "login.h"
#include "ui_appoint.h"
#include<QMainWindow>
#include<QGridLayout>
#include<QPushButton>
#include<QWidget>
#include<QToolBar>
#include<QAction>
#include<QQuickView>
#include<QApplication>
#include<QUrl>
#include<QQmlContext>
#include<QVariant>
#include<QQmlContext>
#include<QQmlApplicationEngine>

namespace Ui {
class MainWindow;
class appoint;
}
class MainWindow;
class AppointView;
/////////////////MainWindow///////////////////////////////
class AppointView:public QDialog
{
    Q_OBJECT
private:
    Ui::appoint *ui;
    QString userId, plateId;
public:
    AppointView(QWidget *parent=0);
    void Appointing();
    void Removing();
    QString UserId();
    QString PlateId();
};

/////////////////MainWindow///////////////////////////////
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QGridLayout *layout;
    vector <Plate*> plates;
    QWidget *background;
    QToolBar *toolbar;
    QAction *logout,*exit,*account_info,*appoint,*remove;
    Ui::MainWindow *ui;
//    QQuickView *view;
//    QQmlApplicationEngine *view1;
    AppointView *manager_View;

public:
    explicit MainWindow(QWidget *parent=0);
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
