#ifndef LOGIN_H
#define LOGIN_H

#include "user.h"
#include "header.h"

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

// 类的前置申明
class QLabel;
class QLineEdit;
class QPushButton;

class Login: public QDialog
{

public:
    explicit Login(User **user);
    virtual ~Login(){}

private:
    QLabel *userLabel;
    QLabel *pwdLabel;

    QLineEdit *userLineEdit;
    QLineEdit *pwdLineEdit;

    QPushButton *loginBtn;
    QPushButton *exitBtn;

    User **user;


private slots:// 声明槽函数
    void login();


};

#endif // LOGIN_H
