#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFile>
#include <QUrl>



// 类的前置申明
class QLabel;
class QLineEdit;
class QPushButton;

class LoginView: public QDialog
{
public:
    explicit LoginView(QWidget *parent=0);
    virtual ~LoginView(){}

private:
    QLabel *userLabel;
    QLabel *pwdLabel;

    QLineEdit *userLineEdit;
    QLineEdit *pwdLineEdit;

    QPushButton *loginBtn;
    QPushButton *exitBtn;

public:
    QString Pwd(QString id);
private slots:// 声明槽函数
    void login();
    void Exit();

};

#endif // LOGINVIEW_H
