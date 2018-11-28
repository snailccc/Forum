#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("Fox-BBS"));
    this->resize(QSize(1600,800));

    Plate *test_post1 = new Plate(this, 1001, "plate_test1");
    Plate *test_post2 = new Plate(this, 1002, "plate_test2");

    plates.push_back(test_post1);
    plates.push_back(test_post2);

    Initial_Action();
    Initial_Background();

}

void MainWindow::Initial_Background()
{
    this->background = new QWidget();
    this->setCentralWidget(this->background);
    this->layout = new QGridLayout(this);
    this->layout->setContentsMargins(10,10,10,10);
    this->layout->setHorizontalSpacing(10);

    ui->mainToolBar->addAction(this->get_info);
    ui->mainToolBar->addAction(this->switch_account);
    ui->mainToolBar->addAction(this->exit);

    for(int i=0;i<plates.size();i++)
    {
        Plate *post = plates[i];
        this->layout->addWidget(post,i,0,1,1);
    }

    this->background->setLayout(this->layout);

}

void MainWindow::Initial_Action()
{
    this->switch_account = new QAction(tr("切换账户"),this);
    this->get_info = new QAction(tr("账户信息"),this);
    this->exit = new QAction(tr("退出"),this);

}


MainWindow::~MainWindow()
{
    delete ui;
}
