#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "plate.h"
#include "header.h"

#include<QMainWindow>
#include<QGridLayout>
#include<QPushButton>
#include<QWidget>
#include<QToolBar>
#include<QAction>

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

public:
    explicit MainWindow(QWidget *parent = 0);
    void Initial_Background();
    void Initial_Action();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
