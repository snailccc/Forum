#include "login.h"

Login_View::Login_View(QWidget *parent):
    QDialog(parent)
{
//    QFile user_group("qrc://user/list_user.qml");
//    if(!user_group.open(QIODevice::ReadOnly|QIODevice::Text))
//    {
//        QMessageBox::warning(this,tr("error"),tr("load data error！"),QMessageBox::Yes);
//        exit(0);
//    }
//    else
//    {
//        QByteArray line = user_group.readLine();
//        QString str(line);
//        qDebug()<< str;
//    }
//    exit(0);
    USER_GROUP[""] = "";
    USER_GROUP["u1"] = "";
    USER_GROUP["u2"] = "";
    USER_GROUP["u3"] = "";
    USER_GROUP["m1"] = "";
    USER_GROUP["m2"] = "";
    USER_GROUP["h1"] = "";
    USER_GROUP["h2"] = "";

    // 创建一个userLabel 这里的this表示父布局是自己
    userLabel = new QLabel(this);
    // 移动到某个位置
    userLabel->move(50,80);
    // 设置显示的文本
    userLabel->setText(tr("user id:"));

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


    connect(loginBtn,&QPushButton::clicked,this,&Login_View::login);
    // close 是QWidget里面的函数表示用来关闭控件
    connect(exitBtn,&QPushButton::clicked,this,&Login_View::Exit);

}


void Login_View::login(){
    // 判断登录的用户名和密码是否正确
    QString id=userLineEdit->text();
    QString password = pwdLineEdit->text();
    if(USER_GROUP.find(id)!=USER_GROUP.end()){
        if(USER_GROUP[id] == password){
            if(USER_TYPE_GROUP[id]==COMMENT_USER)
            {
                user = new User(id);
            }
            else if(USER_TYPE_GROUP[id]==MANAGER_USER)
            {
                user = new Manager(id);
            }
            else if(USER_TYPE_GROUP[id]==HOST_USER)
            {
                int plateId = HOST_GROUP[id];
                user = new Hoster(id,plateId);
            }
            accept();
            return;
        }
    }

    QMessageBox::warning(this,tr("warning"),tr("user name or user pwd error！"),QMessageBox::Yes);
    // 清空内容和指定焦点
//    userLineEdit->clear();
    pwdLineEdit->clear();
//    userLineEdit->setFocus();
}

QString Login_View::Pwd(QString id)
{
    return USER_GROUP[id];
}

void Login_View::Exit()
{
    exit(0);
}
