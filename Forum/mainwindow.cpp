#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("Fox-BBS"));

    Plate *test_post1 = new Plate(this, 1001, "plate_test1");
    Plate *test_post2 = new Plate(this, 1002, "plate_test2");

    plates.push_back(test_post1);
    plates.push_back(test_post2);

    Initial_Action();
    Initial_Background();

    view = new QQuickView();

    //////////////test/////////////////////
    test_post1->AddPost(new Post(0,100001,"post_test1","fox test1","u1"));
    test_post1->AddPost(new Post(0,100002,"post_test2","fox test2","u2"));
    test_post1->AddPost(new Post(0,100003,"post_test2","fox test2","u3"));
}

void MainWindow::Initial_Background()
{
    ui->mainToolBar->addAction(this->account_info);
    ui->mainToolBar->addAction(this->logout);
    ui->mainToolBar->addAction(this->exit);

    for(int i=0;i<plates.size();i++)
    {
        Plate *plate = plates[i];
        ui->plates_layout->addWidget(plate);
        connect(plate,SIGNAL(clicked(bool)),this,SLOT(Create_Plate_View()));
    }

}

void MainWindow::Initial_Action()
{
    this->logout = new QAction(tr("注销"),this);
    connect(logout,SIGNAL(triggered(bool)),this,SLOT(Logout()));
    this->account_info = new QAction(tr("账户"),this);
    connect(account_info,SIGNAL(triggered(bool)),this,SLOT(Get_Account_Info()));
    this->exit = new QAction(tr("退出"),this);
    connect(exit,SIGNAL(triggered(bool)),this,SLOT(close()));

}

void MainWindow::Create_Plate_View()
{
    Plate *plate = qobject_cast<Plate *>(sender());
    int id = plate->get_id();
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

void MainWindow::Logout()
{
    this->hide();
    login = new Login(&user);
    login->show();
    if(login->exec()==QDialog::Accepted)
    {
        this->show();
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
