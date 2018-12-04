#ifndef USER_H
#define USER_H

#include "header.h"
#include "login.h"
#include "ui_user_info.h"

class User;
class User_Info_View;
class Login_View;
class Manager;
class Hoster;

extern User *user;
extern map<QString, int>USER_TYPE_GROUP;
extern map<QString,QString>USER_NAME_GROUP;
extern map<QString, int>HOST_GROUP;

///////////////////////////User_Info_View//////////////////////
class User_Info_View:public QDialog
{
    Q_OBJECT
private:
    Ui::user_info *ui;
    QString username,id;
public:
    User_Info_View(QWidget *parent,QString username,QString id);
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
    Login_View *loginView;
    User(QString id,QWidget *parent=0);
    QString ID();
    QString Name();
    QString Pwd();
    int Type();
    void Show_Info();
    void Login();
    int Logout();
    virtual void Appointing(QString userId,int plateId){}
    virtual void Removing(QString userId){}
    virtual int PlateId(){}
    ~User(){}
};

//////////////////////Manger//////////////////////////
class Manager:public User
{
private:
public:
    Manager(QString id);
    virtual void Appointing(QString userId,int plateId);
    virtual void Removing(QString userId);
};

///////////////////Hoster///////////////////////////
class Hoster:public User
{
private:
    int plateId;
public:
    Hoster(QString id,int plateId, QWidget *parent=0);
    int PlateId();
};

#endif // USER_H
