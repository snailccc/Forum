#include "client.h"

vector<User*>clients;
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

/////////////////Client///////////////////////////////
Client::Client(int index, QWidget *parent) :
    QMainWindow(parent),ui(new Ui::Client),index(index)
{
    //初始化网络连接
    initTCP();

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

void Client::initTCP()
{
    socket = new QTcpSocket(this);
    connectServer();
}

void Client::connectServer()
{
    socket->abort();
    socket->connectToHost("127.0.0.1",666);
    connect(socket,SIGNAL(readyRead()),this,SLOT(receiveData()));
}

void Client::AddPost(QStringList segs)
{
    int plateId = segs[4].toInt();
    for(int i=0;i<plates.size();i++)
    {
        if(plates[i]->Id()==plateId)
        {
            plates[i]->AddPost(segs);
            return;
        }
    }
}

void Client::DelPost(QStringList segs)
{
    int plateId =segs[2].toInt();
    for(int i=0;i<plates.size();i++)
    {
        if(plates[i]->Id()==plateId)
        {
            plates[i]->DelPost(segs);
            return;
        }
    }
}

void Client::AddComment(QStringList segs)
{
    int plateId = segs[5].toInt();
    for(int i=0;i<plates.size();i++)
    {
        if(plates[i]->Id()==plateId)
        {
            plates[i]->AddComment(segs);
            return;
        }
    }
}

void Client::DelComment(QString commentId)
{
    int plateId = commentId.mid(0,3).toInt();
    for(int i=0;i<plates.size();i++)
    {
        if(plates[i]->Id()==plateId)
        {
            plates[i]->DelComment(commentId);
            return;
        }
    }
}

void Client::sendData(QString message)
{
    socket->write(message.toUtf8());
}

void Client::receiveData()
{
    QString message = socket->readAll();
    qDebug()<<"client "<<index<<" receive:"<<message<<endl;
    QStringList segs = message.split("|");
    int op = segs[0].toInt();
    segs.removeOne(segs.front());
    if(op==op_addpost)
    {
        AddPost(segs);
    }
    else if(op==op_delpost)
    {
        DelPost(segs);
    }
    else if(op==op_addcomment)
    {
        AddComment(segs);
    }
    else if(op==op_delcomment)
    {
        DelComment(segs[0]);
    }
    else if(op==op_appoint)
    {
        clients[index]->Appointing(segs[0],segs[1].toInt());
    }
    else if(op==op_remove)
    {
        clients[index]->Removing(segs[0]);
    }

}

void Client::disconnectServer()
{
    qDebug()<<"disconnectServer"<<endl;
}

void Client::Initial_Background()
{
    ui->mainToolBar->addAction(this->account_info);
    ui->mainToolBar->addAction(this->appoint);
    ui->mainToolBar->addAction(this->remove);
    ui->mainToolBar->addAction(this->logout);
    ui->mainToolBar->addAction(this->exit);

    ui->mainToolBar->setStyleSheet("Color:white");
    //如果用户为管理员，显示任命和移除选项

    if(clients[index]->Type()!=MANAGER)
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

void Client::Initial_Action()//菜单栏选项连接对应函数
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

void Client::Create_Plate_View()//打开板块界面
{
    Plate *plate = qobject_cast<Plate *>(sender());
    QString title = plate->get_title();
    plate->Show(index,socket);
}

void Client::Get_Account_Info()//打开用户信息界面
{
    clients[index]->ShowInfo();
}

void Client::Change_Background(int old_type)//切换用户后修改主界面
{
    if(clients[index]->Type()!=MANAGER && old_type==MANAGER)
    {
        this->appoint->setVisible(0);
        this->remove->setVisible(0);
    }
    else if(clients[index]->Type()==MANAGER && old_type!=MANAGER)
    {
        this->appoint->setVisible(1);
        this->remove->setVisible(1);
    }
}

void Client::Logout()//用户登出
{
    this->hide();
    int old_type = clients[index]->Type();
    if(clients[index]->Logout()==QDialog::Accepted)
    {
        this->Change_Background(old_type);
        this->show();
    }
    else
    {
        this->close();
    }
}

void Client::Appointing()//打开任命窗口
{
    manager_View = new AppointView;
    manager_View->show();
    if(manager_View->exec()==QDialog::Accepted)
    {
        QString userId = manager_View->UserId();
        int plateId = manager_View->PlateId().toInt();
        QString message = QString::number(op_appoint) + "|" + userId + "|" + QString::number(plateId) + "|" +clients[index]->ID();
        sendData(message);        
    }
}

void Client::Removing()//打开撤销版主窗口
{
    manager_View =  new AppointView(1);
    manager_View->show();
    if(manager_View->exec()==QDialog::Accepted)
    {
        QString userId = manager_View->UserId();
        QString message = QString::number(op_remove) + "|" + userId + "|" +clients[index]->ID();
        sendData(message);
    }
}

vector<Plate*>& operator<< (vector<Plate*>&plates, QSqlDatabase db)//重载数据库导出板块数据符号
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

void Client::closeEvent(QCloseEvent *event)
{
    socket->close();
}

Client::~Client()
{
    delete ui;
}
