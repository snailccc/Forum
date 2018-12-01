#include "user.h"
User *user = NULL;

map<QString, QString>user_name_group = {
    { "u1", "fox1" },
    { "u2", "fox1" },
    { "a1", "fox1" },
    { "a2", "fox1" }
};

//////////////////////////User_Info_View///////////////////////////////
User_Info_View::User_Info_View(QWidget *parent, QString username, QString id):
    ui(new Ui::user_info),username(username),id(id)
{
    ui->setupUi(this);
    ui->id->setText(id);
    ui->username->setText(username);
}

//////////////////////////User///////////////////////////////
User::User(QString id,QString password):
    id(id),password(password)
{
    userName = user_name_group[id];
}

QString User::ID()
{
    return id;
}

void User::Show_Info()
{
    info = new User_Info_View(0,userName,id);
    info->show();
}
