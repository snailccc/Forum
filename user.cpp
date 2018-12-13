#include "user.h"
#include "global.h"
#include "loginview.h"

extern map<QString, Base>userGroup;
//////////////////////Base//////////////////////////
Base::Base(QString id, QString pwd, QString username, int type, int plateId):
    id(id),username(username),pwd(pwd),type(type)
{
    if(type == HOST_USER)
    {
        this->plateId = plateId;
    }
}


//////////////////////User//////////////////////////
User::User(QString id, QString pwd, QString username, int type):
    id(id),userName(username),pwd(pwd),type(type)
{
    loginView = new LoginView;

}

User::User(Base base)
{
    id = base.id;
    userName = base.username;
    pwd = base.pwd;
    type = base.type;

    loginView = new LoginView;
}

void User::Login()
{

    loginView->show();
}

int User::Logout()
{
    Login();
    if(loginView->exec()==QDialog::Accepted)
    {
        loginView->close();
        return QDialog::Accepted;
    }
    else if(loginView->exec()==QDialog::Rejected)
    {
        loginView->close();
        return QDialog::Rejected;
    }
}

QString User::ID()
{
    return id;
}

QString User::Pwd()
{
    return pwd;
}

QString User::Name()
{
    return userName;
}

int User::Type()
{
    return type;
}

void User::ShowInfo()
{
    info = new User_Info_View(userName,id);
    info->show();
//    delete info;
}

void User::Appointing(QString userId, int plateId)
{

}

void User::Removing(QString userId)
{

}

//////////////////////Manger//////////////////////////
Manager::Manager(Base base):
    User(base)
{
    qDebug()<<"Manager"<<endl;
}

void Manager::Appointing(QString userId, int plateId)
{
    userGroup[userId].type = HOST_USER;
    userGroup[userId].plateId = plateId;
    QSqlQuery query(db);
    query.exec("update user set type="+QString::number(HOST_USER)+" where id="+userId);

}

void Manager::Removing(QString userId)
{
    userGroup[userId].type = COMMENT_USER;
    QSqlQuery query(db);
    query.exec("update user set type="+QString::number(COMMENT_USER)+" where id="+userId);
}


//////////////////////Hoster//////////////////////////
Hoster::Hoster(Base base):
    User(base),plateId(base.plateId)
{
    qDebug()<<"Hoster"<<endl;
}

int Hoster::PlateId()
{
    return plateId;
}

//////////////////////////User_Info_View///////////////////////////////
User_Info_View::User_Info_View(QString username, QString id, QWidget *parent):
    QDialog(parent),ui(new Ui::user_info),username(username),id(id)
{
    ui->setupUi(this);
    ui->id->setText(id);
    ui->username->setText(username);
    int type = user->Type();
    if(type==COMMENT_USER)
    {
        ui->type->setText("User");
    }
    else if(type==HOST_USER)
    {
        ui->type->setText("Moderator of "+QString::number(user->PlateId())+" plate");
    }
    else if(type == MANAGER)
    {
        ui->type->setText("Manager");
    }
}
