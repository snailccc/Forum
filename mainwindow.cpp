#include "mainwindow.h"
#include "ui_mainwindow.h"
/////////////////AppointView///////////////////////////////
AppointView::AppointView(int type, QWidget *parent):
    QDialog(parent),ui(new Ui::appoint)
{
    ui->setupUi(this);
    //判定弹出的是任命框还是移除任命框，type=0为任命框，否则为移除任命框
    if(type == 0)
    {
        this->setWindowTitle("Appointing");
    }
    else
    {
        this->setWindowTitle("Removing");
        ui->mainLayout->removeWidget(ui->label_2);
        delete ui->label_2;
        ui->mainLayout->removeWidget(ui->plateId);
        delete ui->plateId;
    }

}

QString AppointView::UserId()
{
    userId = ui->userId->text();
    return userId;
}

QString AppointView::PlateId()
{
    plateId = ui->plateId->text();
    return plateId;
}

void AppointView::on_buttonBox_accepted()
{
    accept();
}

/////////////////MainWindow///////////////////////////////
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("Fox-Study-BBS"));
    //初始化界面背景图片
    QPalette palette;
    QPixmap pixmap(":/img/bg1");
    palette.setBrush(QPalette::Window,QBrush(pixmap.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    this->setPalette(palette);

    Initial_Action();//初始化菜单栏
    Initial_Background();//初始化板块列表
}

void MainWindow::Initial_Background()
{
    ui->mainToolBar->addAction(this->account_info);
    ui->mainToolBar->addAction(this->appoint);
    ui->mainToolBar->addAction(this->remove);
    ui->mainToolBar->addAction(this->logout);
    ui->mainToolBar->addAction(this->exit);

    ui->mainToolBar->setStyleSheet("Color:white");
    //如果用户为管理员，显示任命和移除选项
    if(user->Type()!=MANAGER)
    {
        this->appoint->setVisible(0);
        this->remove->setVisible(0);
    }
    //初始化板块列表的属性
    ui->plateGroup->horizontalHeader()->hide();
    ui->plateGroup->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->plateGroup->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->plateGroup->verticalHeader()->hide();
    ui->plateGroup->verticalHeader()->setDefaultSectionSize(50);

    plates<<db ;
    //插入帖子
    int n = plates.size();
    ui->plateGroup->setRowCount(n*2+1);
    for(int i=0;i<n;i++)
    {
        Plate *plate = plates[i];
        ui->plateGroup->setCellWidget(i*2+1,0,plate);
        connect(plate,SIGNAL(clicked(bool)),this,SLOT(Create_Plate_View()));
    }
}

void MainWindow::Initial_Action()//菜单栏选项连接对应函数
{
    this->logout = new QAction(tr("Logout"),this);
    connect(logout,SIGNAL(triggered(bool)),this,SLOT(Logout()));

    this->appoint = new QAction(tr("Apoint Hoster"),this);
    connect(appoint,SIGNAL(triggered(bool)),this,SLOT(Appointing()));

    this->remove = new QAction(tr("Remove Hoster"),this);
    connect(remove,SIGNAL(triggered(bool)),this,SLOT(Removing()));

    this->account_info = new QAction(tr("Account"),this);
    connect(account_info,SIGNAL(triggered(bool)),this,SLOT(Get_Account_Info()));

    this->exit = new QAction(tr("Exit"),this);
    connect(exit,SIGNAL(triggered(bool)),this,SLOT(close()));

    update();
}

void MainWindow::Create_Plate_View()//打开板块界面
{
    Plate *plate = qobject_cast<Plate *>(sender());
    QString title = plate->get_title();
    plate->Show();
}

void MainWindow::Get_Account_Info()//打开用户信息界面
{
    user->ShowInfo();
}

void MainWindow::Change_Background(int old_type)//切换用户后修改主界面
{
    if(user->Type()!=MANAGER && old_type==MANAGER)
    {
        this->appoint->setVisible(0);
        this->remove->setVisible(0);
    }
    else if(user->Type()==MANAGER && old_type!=MANAGER)
    {
        this->appoint->setVisible(1);
        this->remove->setVisible(1);
    }
}

void MainWindow::Logout()//用户登出
{
    this->hide();
    int old_type = user->Type();
    if(user->Logout()==QDialog::Accepted)
    {
        this->Change_Background(old_type);
        this->show();
    }
    else
    {
        this->close();
    }

}

void MainWindow::Appointing()//打开任命窗口
{
    manager_View = new AppointView;
    manager_View->show();
    if(manager_View->exec()==QDialog::Accepted)
    {
        QString userId = manager_View->UserId();
        int plateId = manager_View->PlateId().toInt();
        user->Appointing(userId,plateId);
    }
}

void MainWindow::Removing()//打开撤销版主窗口
{
    manager_View =  new AppointView(1);
    manager_View->show();
    if(manager_View->exec()==QDialog::Accepted)
    {
        QString userId = manager_View->UserId();
        user->Removing(userId);
    }
}

vector<Plate*>& operator <<(vector<Plate*>&plates, QSqlDatabase db)//重载数据库导出板块数据符号
{
    QSqlQuery query(db);
    if(!query.exec("select * from plates"))
    {
        QMessageBox::warning(0,QObject::tr("database connect error"),QObject::tr("please check your internet connect and database"));
        exit(0);
    }

    while(query.next())
    {
        int id = query.value(0).toInt();
        QString title = query.value(1).toString();
        plates.push_back(new Plate(id, title));
    }
    return plates;
}

MainWindow::~MainWindow()
{
    delete ui;
}

