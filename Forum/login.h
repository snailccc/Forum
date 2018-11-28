#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

// 类的前置申明
class QLabel;
class QLineEdit;
class QPushButton;

class Login: public QDialog
{

public:
    explicit Login(QWidget *prent = nullptr);
    virtual ~Login(){}

private:
    // 定义一些控件的对象指针
    // QLable 相当于android中的textView
    QLabel *userLabel;
    QLabel *pwdLabel;

    // QLineEdit 相当于android中的EditText
    QLineEdit *userLineEdit;
    QLineEdit *pwdLineEdit;

    // QPushButton 相当于android的Button
    QPushButton *loginBtn;
    QPushButton *exitBtn;


private slots:// 声明槽函数
    void login();


};

#endif // LOGIN_H
