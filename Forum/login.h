#ifndef LOGIN_H
#define LOGIN_H

#include "user.h"
#include "header.h"

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QUrl>

// 类的前置申明
class QLabel;
class QLineEdit;
class QPushButton;

class Login_View: public QDialog
{
public:
    explicit Login_View(QWidget *parent=0);
    virtual ~Login_View(){}

private:
    QLabel *userLabel;
    QLabel *pwdLabel;

    QLineEdit *userLineEdit;
    QLineEdit *pwdLineEdit;

    QPushButton *loginBtn;
    QPushButton *exitBtn;

//    User **user;

    map<QString, QString>USER_GROUP;
public:
    QString Pwd(QString id);
private slots:// 声明槽函数
    void login();

};

#endif // LOGIN_H
