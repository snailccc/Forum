#include "user.h"
User *user = NULL;

map <QString,QString> USER_NAME_GROUP={
    {"",""},
    {"u1","fox1"},
    {"u2","fox2"},
    {"u3","fox3"},
    {"m1","fox4"},
    {"m2","fox5"},
    {"h1","fox6"},
    {"h2","fox7"},
};

map <QString,int> USER_TYPE_GROUP={
    {"",COMMENT_USER},
    {"u1",COMMENT_USER},
    {"u2",COMMENT_USER},
    {"u3",COMMENT_USER},
    {"m1",MANAGER_USER},
    {"m2",MANAGER_USER},
    {"h1",HOST_USER},
    {"h2",HOST_USER},
};

map<QString,int>HOST_GROUP = {
    {"h1",101},
    {"h2",102}
};

//////////////////////////User_Info_View///////////////////////////////
User_Info_View::User_Info_View(QWidget *parent, QString username, QString id):
    QDialog(parent),ui(new Ui::user_info),username(username),id(id)
{
    ui->setupUi(this);
    ui->id->setText(id);
    ui->username->setText(username);
}

//////////////////////////User///////////////////////////////
User::User(QString id,QWidget *parent):
    QObject(parent),id(id)
{
    loginView = new Login_View();
    pwd = loginView->Pwd(id);
    userName = USER_NAME_GROUP[id];
    type = USER_TYPE_GROUP[id];
}

QString User::ID()
{
    return id;
}

QString User::Name()
{
    return userName;
}

int User::Type()
{
    return type;
}

void User::Show_Info()
{
    info = new User_Info_View(0,userName,id);
    info->show();
}

void User::Logout()
{
    Login();
    loginView->show();
    while(loginView->exec()!=QDialog::Accepted);
}

void User::Login()
{
    loginView = new Login_View();
}

//////////////////////Manager//////////////////////////
Manager::Manager(QString id):
    User(id)
{

}

void Manager::Appointing(QString userId, int plateId)
{
    if(USER_TYPE_GROUP[userId]!=MANAGER_USER)
    {
        QMessageBox::warning(0,tr("warning"),tr("权限不足，任命失败"),QMessageBox::Yes);
        return;
    }
    USER_TYPE_GROUP[userId] = MANAGER_USER;
    HOST_GROUP[userId] = plateId;
}

void Manager::Removing(QString userId)
{
    if(USER_TYPE_GROUP[userId]!=HOST_USER)
    {
        QMessageBox::warning(0,tr("warning"),tr("该用户不是版主"),QMessageBox::Yes);
        return;
    }
    USER_TYPE_GROUP[userId] =COMMENT_USER;
    HOST_GROUP.erase(userId);
}

///////////////////Hoster///////////////////////////
Hoster::Hoster(QString id,int plateId,QWidget *parent):
    User(id,parent),plateId(plateId)
{

}

int Hoster::PlateId()
{
    return plateId;
}
