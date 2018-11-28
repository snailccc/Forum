#include "login.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>


Login::Login(QWidget *prent):QDialog (prent)
{
    // 创建一个userLabel 这里的this表示父布局是自己
    userLabel = new QLabel(this);
    // 移动到某个位置
    userLabel->move(50,80);
    // 设置显示的文本
    userLabel->setText(tr("user name:"));

    // 登录输入框
    userLineEdit = new QLineEdit(this);
    userLineEdit->move(140,80);
    // 设置hint效果
    userLineEdit->setPlaceholderText(tr("please input user name"));


    // 创建一个userLabel 这里的this表示父布局是自己
    pwdLabel = new QLabel(this);
    // 移动到某个位置
    pwdLabel->move(50,130);
    // 设置显示的文本
    pwdLabel->setText(tr("user pwd:"));

    // 登录输入框
    pwdLineEdit = new QLineEdit(this);
    pwdLineEdit->move(140,130);
    // 设置hint效果
    pwdLineEdit->setPlaceholderText(tr("please input user pwd"));
    pwdLineEdit->setEchoMode(QLineEdit::Password);



    loginBtn = new QPushButton(this);
    loginBtn->move(50,200);
    loginBtn->setText(tr("login"));


    exitBtn = new QPushButton(this);
    exitBtn->move(210,200);
    exitBtn->setText(tr("exit"));


    connect(loginBtn,&QPushButton::clicked,this,&Login::login);
    // close 是QWidget里面的函数表示用来关闭控件
    connect(exitBtn,&QPushButton::clicked,this,&Login::close);

}




void Login::login(){
    // 判断登录的用户名和密码是否正确
    if(userLineEdit->text().trimmed()==tr("")&&
            pwdLineEdit->text().trimmed()==tr("")){
        accept();
    }else{
        QMessageBox::warning(this,tr("warning"),tr("user name or user pwd error！"),QMessageBox::Yes);

        // 清空内容和指定焦点
        userLineEdit->clear();
        pwdLineEdit->clear();
        userLineEdit->setFocus();
    }
}
