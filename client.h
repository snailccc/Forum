#ifndef CLIENT_H
#define CLIENT_H

#include "plate.h"
#include "user.h"
#include "loginview.h"
#include "ui_appoint.h"
#include "ui_client.h"
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
#include<QWindow>

namespace Ui {
    class Client;
    class appoint;
}

class Client;
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

/////////////////////////Client//////////////////////////////////
class Client:public QMainWindow
{
    Q_OBJECT
private:
    int index;
    QGridLayout *layout;
    vector<Plate*> plates;
    QWidget *background;
    QToolBar *toolbar;
    QAction *logout,*exit,*account_info,*appoint,*remove;
    Ui::Client *ui;
    AppointView *manager_View;

    QTcpSocket *socket;
    QTcpServer *server;

public:
    explicit Client(int index, QWidget *parent=0);
    friend vector<Plate*>& operator <<(vector<Plate*>& plateGroup, QSqlDatabase db);
    void Initial_Background();
    void Change_Background(int old_type);
    void Initial_Action();
    void initTCP();
    void newConnect();
    ~Client();
protected slots:
    void Create_Plate_View();
    void Logout();
    void Get_Account_Info();
    void Appointing();
    void Removing();
    void connectServer();
    void disconnectServer();
    void sendData(QString message);
    void receiveData();

};



#endif // CLIENT_H
