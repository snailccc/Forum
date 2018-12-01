#ifndef USER_H
#define USER_H

#include "header.h"
#include "ui_user_info.h"
class User;
class User_Info_View;
extern User *user;

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
class User
{
private:
    QString id,userName, password;
    User_Info_View *info;
public:
    User(QString id,QString password);
    QString ID();
    void Show_Info();
    ~User();
};

#endif // USER_H
