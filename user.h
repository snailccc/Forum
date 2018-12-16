#ifndef USER_H
#define USER_H

#include "loginview.h"
#include "ui_user_info.h"
#include <QString>
#include <QObject>
#include <QWidget>
#include <QSqlDatabase>

class User_Info_View;
class User;
class Base;
class Anonymous;
//////////////////////////Base////////////////////
class Base
{
public:
    QString id, username, pwd;
    int type;
    int plateId;
    Base(QString id, QString pwd, QString username, int type, int plateId=0);
    Base(){}
};

//////////////////////////User_Info_View////////////////////
class User_Info_View:public QDialog
{
private:
    Ui::user_info *ui;
    QString username,id;
public:
    User_Info_View(QString username,QString id,QWidget *parent=0);
};

//////////////////////////User///////////////////////////////
class User:public QObject
{
    Q_OBJECT
private:
    QString id, userName, pwd;
    User_Info_View *info;
    int type;
public:
    LoginView *loginView;
    User(QString id, QString pwd, QString username, int type);
    User(Base base);
    User(){loginView = new LoginView;}
    QString ID();
    QString Name();
    QString Pwd();
    int Type();
    void ShowInfo();
    void Login();
    int Logout();
    virtual void Appointing(QString userId,int plateId);
    virtual void Removing(QString userId);
    virtual int PlateId(){return 0;}
    ~User(){}
};

//////////////////////Manger//////////////////////////
class Manager:public User
{
private:
public:
    Manager(Base base);
//    friend Base& operator >>(Base& base, QSqlDatabase db);
    friend Base& operator >>(Base& base, QSqlDatabase db);
    virtual void Appointing(QString userId,int plateId);
    virtual void Removing(QString userId);
};

///////////////////Hoster///////////////////////////
class Hoster:public User
{
private:
    int plateId;
public:
    Hoster(Base base);
    int PlateId();
};

///////////////////Anonymous///////////////////////////
class Anonymous:public User
{
private:
    QString id, userName, pwd;
    int type;
public:
    Anonymous(Base base);
};

#endif // USER_H
