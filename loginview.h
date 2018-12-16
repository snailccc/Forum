#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFile>
#include <QUrl>

#include "ui_login.h"
#include "ui_signin.h"

// 类的前置申明
class QLabel;
class QLineEdit;
class QPushButton;
class SignInView;

class LoginView: public QDialog
{
public:
    explicit LoginView(QWidget *parent=0);
    virtual ~LoginView(){}
private:
    Ui::Login *ui;
public:
    QString Pwd(QString id);
private slots:// 声明槽函数
    void login();
    void AnonmousLogin();
    void SignUp();
    void on_SignUp_clicked(bool checked);
};

class SignInView:public QDialog
{
private:
    Ui::SignIn *ui;
public:
    explicit SignInView(QWidget *parent=0);
    ~SignInView();
private slots:
    void on_ok_clicked(bool checked);
};

#endif // LOGINVIEW_H
