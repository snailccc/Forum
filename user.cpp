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
    info = new User_Info_View(userName,id);
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
    base>>db;
}

void Manager::Removing(QString userId)//移除版主
{
    userGroup[userId].type = COMMENT_USER;
    Base base = userGroup[userId];
    base>>db;
}

Base& operator>> (Base& base, QSqlDatabase db)//重载运算符，更新用户信息
{
    QSqlQuery query(db);
    if(base.type==HOST_USER)
    {
        query.prepare("update user set type=?,plateId=? where id=?");
        query.addBindValue(QString::number(base.type));
        query.addBindValue(base.plateId);
    }
    else if(base.type==COMMENT_USER)
    {
        query.prepare("update user set type=? where id=?");
        query.addBindValue(QString::number(base.type));
    }
    query.addBindValue(base.id);
    if(!query.exec())
    {
        QMessageBox::warning(0,QObject::tr("database connect error"),QObject::tr("please check your internet connect and database"));
        exit(0);
    }
    return base;
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

//////////////////////Hoster//////////////////////////
Anonymous::Anonymous(Base base):
    User (base)
{
    qDebug()<<"Anonymous"<<endl;
}


//////////////////////////User_Info_View///////////////////////////////
User_Info_View::User_Info_View(QString username, QString id, QWidget *parent):
    QDialog(parent),ui(new Ui::user_info),username(username),id(id)
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
    else if(type == ANONYMOUS)
    {
        ui->type->setText("Anonymous");
    }
}

