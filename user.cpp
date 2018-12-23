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

void User::Login()//打开登录界面
{

    loginView->show();
}

int User::Logout()//用户注销
{
    Login();
    int res = loginView->exec();
    if(res==QDialog::Accepted)
    {
        loginView->close();
        return QDialog::Accepted;
    }
    else if(res==QDialog::Rejected)
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
    info = new User_Info_View(type,userName,id);
    info->show();
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

void Manager::Appointing(QString userId, int plateId)//任命版主
{
    userGroup[userId].type = HOST_USER;
    userGroup[userId].plateId = plateId;
    Base base = userGroup[userId];
}

void Manager::Removing(QString userId)//移除版主
{
    userGroup[userId].type = COMMENT_USER;
    Base base = userGroup[userId];
}


//////////////////////Hoster//////////////////////////
Hoster::Hoster(Base base):
    User(base),plateId(base.plateId)
{
    qDebug()<<"Hoster plateId"<<plateId<<endl;
}

int Hoster::PlateId()
{
    return plateId;
}

void Hoster::ShowInfo()
{
    info = new User_Info_View(User::Type(),User::Name(),User::ID(),plateId);
    info->show();
}


//////////////////////Hoster//////////////////////////
Anonymous::Anonymous(Base base):
    User (base)
{
    qDebug()<<"Anonymous"<<endl;
}


//////////////////////////User_Info_View///////////////////////////////
User_Info_View::User_Info_View(int type, QString username, QString id, int plateId, QWidget *parent):
    QDialog(parent),ui(new Ui::user_info),username(username),id(id),type(type)
{
    ui->setupUi(this);
    this->setWindowTitle("Account");
    QPalette palette;
    QPixmap pixmap(":/img/bg1");
    palette.setBrush(QPalette::Window,QBrush(pixmap.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    this->setPalette(palette);

    //根据用户信息显示用户身份
    ui->id->setText(id);
    ui->username->setText(username);

    if(type==COMMENT_USER)
    {
        ui->type->setText("User");
    }
    else if(type==HOST_USER)
    {
        ui->type->setText("Moderator of "+QString::number(plateId)+" plate");
    }
    else if(type == MANAGER)
    {
        ui->type->setText("Manager");
    }
    else if(type == ANONYMOUS)
    {
        ui->type->setText("Anonymous");
    }
}

