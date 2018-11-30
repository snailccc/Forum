#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "plate.h"
#include "header.h"
#include "user.h"

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
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:

    QGridLayout *layout;
    vector <Plate*> plates;
    QWidget *background;
    QToolBar *toolbar;
    QAction *switch_account,*exit,*get_info;
    Ui::MainWindow *ui;
    QQuickView *view;
    QQmlApplicationEngine *view1;
    User *user;


public:
    explicit MainWindow(QWidget *parent = 0,User *user = 0);
    void Initial_Background();
    void Initial_Action();
    ~MainWindow();
protected slots:
    void Create_Plate_View();
};

#endif // MAINWINDOW_H
