#include "loginview.h"
#include "global.h"
map<QString, Base>userGroup;

LoginView::LoginView(QWidget *parent):
    QDialog(parent),ui(new Ui::Login)
{
    ui->setupUi(this);                          //初始化登录界面
    this->setFixedSize(500,400);
    QPalette palette;
    QPixmap pixmap(":/img/bg1");
    palette.setBrush(QPalette::Window,QBrush(pixmap.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    this->setPalette(palette);

    connect(ui->SignIn,&QPushButton::clicked,this,&LoginView::login);
    connect(ui->Anonmous,&QPushButton::clicked,this,&LoginView::AnonmousLogin);
    connect(ui->SignUp,&QPushButton::clicked,this,&LoginView::on_SignUp_clicked);
}

void LoginView::login(){
    QString id=ui->Id->text();
    QString password = ui->pwd->text();
    // 判断登录的用户名和密码是否正确
    if(userGroup.count(id)) {
        Base base = userGroup[id];
        if(base.pwd == password)
        {
            //根据用户的类型实例化
            if(base.type == COMMENT_USER)
            {
                user = new User(base);
            }
            else if(base.type == MANAGER)
            {
                user = new Manager(base);
            }
            else if(base.type == HOST_USER)
            {
                user = new Hoster(base);
            }
            accept();
            return;
        }
    }
    QMessageBox::warning(0,tr("warning"),tr("user id or pwd error"));
    ui->pwd->clear();
}

QString LoginView::Pwd(QString id)
{
    return userGroup[id].pwd;
}

void LoginView::AnonmousLogin()
{
    Base base("anonymous","","unknow",ANONYMOUS);
    user = new Anonymous(base);
    accept();
    return;
}

void LoginView::on_SignUp_clicked(bool checked)//登录界面初始化
{
    SignInView *signin = new SignInView();
    signin->show();
}


//////////////////////////////////SignInView////////////////////////////
SignInView::SignInView(QWidget *parent):
    QDialog (parent),ui(new Ui::SignIn)
{
    ui->setupUi(this);
    this->setFixedSize(500,400);
    connect(ui->ok,&QPushButton::clicked,this,&SignInView::on_ok_clicked);
}


void SignInView::on_ok_clicked(bool checked)    //导入新注册用户信息
{
    QSqlQuery query(db);
    QString id = ui->Id->text();
    if(userGroup.count(id))                     //查找id是否已被使用
    {

        QMessageBox::warning(0,tr("warning"),tr("user id has existed"));
        return;
    }
    QString username = ui->username->text();
    QString pwd = ui->pwd->text();
    query.prepare("insert into user (id,pwd,name,type) values (?,?,?,?)");
    query.addBindValue(id);
    query.addBindValue(pwd);
    query.addBindValue(username);
    query.addBindValue(COMMENT_USER);
    if(!query.exec())
    {
        QMessageBox::warning(0,QObject::tr("database connect error"),QObject::tr("please check your internet connect and database"));
        exit(0);
    }
    else
    {
        QMessageBox::warning(0,QObject::tr("Sign up"),QObject::tr("Successful"));
        userGroup[id] = Base(id, pwd, username, COMMENT_USER);
        accept();
    }

}

SignInView::~SignInView()
{

}
