#include "mainwindow.h"
#include "ui_mainwindow.h"
/////////////////AppointView///////////////////////////////
AppointView::AppointView(QWidget *parent):
    QDialog(parent),ui(new Ui::appoint)
{
    ui->setupUi(this);
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

void AppointView::Appointing()
{
    this->setWindowTitle("Appointing");
}

void AppointView::Removing()
{
    this->setWindowTitle("Removing");
    ui->mainLayout->removeWidget(ui->label_2);
    delete ui->label_2;
    ui->mainLayout->removeWidget(ui->plateId);
    delete ui->plateId;
}

/////////////////MainWindow///////////////////////////////
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("Fox-Study-BBS"));

    Plate *plate1 = new Plate(this, 101, "继承");
    Plate *plate2 = new Plate(this, 102, "封装");
    Plate *plate3 = new Plate(this, 103, "多态");

    plates.push_back(plate1);
    plates.push_back(plate2);
    plates.push_back(plate3);

    Initial_Action();
    Initial_Background();

//    view = new QQuickView();

    //////////////test/////////////////////
    plate1->AddPost(new Post(0,101001,plate1->Id(),"帖子3","fox test1","u1"));
    plate1->AddPost(new Post(0,101002,plate1->Id(),"帖子2","fox test2","u2"));
    plate1->AddPost(new Post(0,101003,plate1->Id(),"帖子1","fox test3","u3"));
    plate2->AddPost(new Post(0,102001,plate2->Id(),"帖子6","fox test4","u1"));
    plate2->AddPost(new Post(0,102002,plate2->Id(),"帖子5","fox test5","u2"));
    plate2->AddPost(new Post(0,102003,plate2->Id(),"帖子4","fox test6","u3"));
    plate3->AddPost(new Post(0,102001,plate3->Id(),"帖子9","fox test4","u1"));
    plate3->AddPost(new Post(0,102002,plate3->Id(),"帖子8","fox test5","u2"));
    plate3->AddPost(new Post(0,102003,plate3->Id(),"帖子7","fox test6","u3"));
}

void MainWindow::Initial_Background()
{    
    ui->mainToolBar->addAction(this->account_info);
    ui->mainToolBar->addAction(this->appoint);
    ui->mainToolBar->addAction(this->remove);
    ui->mainToolBar->addAction(this->logout);
    ui->mainToolBar->addAction(this->exit);

    if(user->Type()!=MANAGER_USER)
    {
        this->appoint->setVisible(0);
        this->remove->setVisible(0);
    }

    ui->plateGroup->horizontalHeader()->hide();
    ui->plateGroup->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->plateGroup->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->plateGroup->verticalHeader()->hide();
    ui->plateGroup->verticalHeader()->setDefaultSectionSize(50);
    int n = plates.size();
    ui->plateGroup->setRowCount(n*2+1);
    for(int i=0;i<n;i++)
    {
        Plate *plate = plates[i];
        ui->plateGroup->setCellWidget(i*2+1,0,plate);
//        ui->plateGroup->setItem(i,0,new QTableWidgetItem());
        connect(plate,SIGNAL(clicked(bool)),this,SLOT(Create_Plate_View()));
    }
}

void MainWindow::Initial_Action()
{
    this->logout = new QAction(tr("注销"),this);
    connect(logout,SIGNAL(triggered(bool)),this,SLOT(Logout()));

    this->appoint = new QAction(tr("任命版主"),this);
    connect(appoint,SIGNAL(triggered(bool)),this,SLOT(Appointing()));

    this->remove = new QAction(tr("撤销版主"),this);
    connect(remove,SIGNAL(triggered(bool)),this,SLOT(Removing()));

    this->account_info = new QAction(tr("账户"),this);
    connect(account_info,SIGNAL(triggered(bool)),this,SLOT(Get_Account_Info()));

    this->exit = new QAction(tr("退出"),this);
    connect(exit,SIGNAL(triggered(bool)),this,SLOT(close()));

    update();
}

void MainWindow::Create_Plate_View()
{
    Plate *plate = qobject_cast<Plate *>(sender());
    //    int id = plate->get_id();
    QString title = plate->get_title();
    plate->Show();

    //    this->view->setTitle(title);
    //    QQmlContext *engine_plate = this->view->rootContext();
    //    engine_plate->setContextProperty("plate_c",plate);

    //    QQmlContext *engine_post = this->view->rootContext();
    //    plate->postgroup->AddPost(Post(100001,"test_post100001","I'm test the post 100001"));
    //    plate->postgroup->AddPost(Post(100002,"test_post100002","I'm test the post 100002"));
    //    engine_post->setContextProperty("postgroup", plate->postgroup);

    //    this->view->setSource(QUrl("qrc:/qml/qml/Plate.qml"));
    //    view->resize(800,600);
    //    view->show();

}

void MainWindow::Get_Account_Info()
{
    user->Show_Info();
}

void MainWindow::Change_Background(int old_type)
{
    if(user->Type()!=MANAGER_USER && old_type==MANAGER_USER)
    {
        this->appoint->setVisible(0);
        this->remove->setVisible(0);
    }
    else if(user->Type()==MANAGER_USER && old_type!=MANAGER_USER)
    {
        this->appoint->setVisible(1);
        this->remove->setVisible(1);
    }
}

void MainWindow::Logout()
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

void MainWindow::Appointing()
{
    manager_View = new AppointView;
    manager_View->Appointing();
    if(manager_View->exec()==QDialog::Accepted)
    {
        QString userId = manager_View->UserId();
        int plateId = manager_View->PlateId().toInt();
        user->Appointing(userId,plateId);
    }

}

void MainWindow::Removing()
{
    manager_View =  new AppointView;
    manager_View->Removing();
    if(manager_View->exec()==QDialog::Accepted)
    {
        QString userId = manager_View->UserId();
        user->Removing(userId);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
