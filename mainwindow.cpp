#include "mainwindow.h"
#include "ui_mainwindow.h"
/////////////////AppointView///////////////////////////////
AppointView::AppointView(int type, QWidget *parent):
    QDialog(parent),ui(new Ui::appoint)
{
    ui->setupUi(this);
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

    Initial_Action();
    Initial_Background();
}

void MainWindow::Initial_Background()
{
    ui->mainToolBar->addAction(this->account_info);
    ui->mainToolBar->addAction(this->appoint);
    ui->mainToolBar->addAction(this->remove);
    ui->mainToolBar->addAction(this->logout);
    ui->mainToolBar->addAction(this->exit);

    if(user->Type()!=MANAGER)
    {
        this->appoint->setVisible(0);
        this->remove->setVisible(0);
    }

    ui->plateGroup->horizontalHeader()->hide();
    ui->plateGroup->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->plateGroup->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->plateGroup->verticalHeader()->hide();
    ui->plateGroup->verticalHeader()->setDefaultSectionSize(50);

    plates<<db ;

    int n = plates.size();
    ui->plateGroup->setRowCount(n*2+1);
    for(int i=0;i<n;i++)
    {
        Plate *plate = plates[i];
        ui->plateGroup->setCellWidget(i*2+1,0,plate);
        connect(plate,SIGNAL(clicked(bool)),this,SLOT(Create_Plate_View()));
    }
}

void MainWindow::Initial_Action()
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

void MainWindow::Create_Plate_View()
{
    Plate *plate = qobject_cast<Plate *>(sender());
    QString title = plate->get_title();
    plate->Show();
}

void MainWindow::Get_Account_Info()
{
    user->ShowInfo();
}

void MainWindow::Change_Background(int old_type)
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
    manager_View->show();
    if(manager_View->exec()==QDialog::Accepted)
    {
        QString userId = manager_View->UserId();
        int plateId = manager_View->PlateId().toInt();
        user->Appointing(userId,plateId);
    }
}

void MainWindow::Removing()
{
    manager_View =  new AppointView(1);
    manager_View->show();
    if(manager_View->exec()==QDialog::Accepted)
    {
        QString userId = manager_View->UserId();
        user->Removing(userId);
    }
}

vector<Plate*>& operator <<(vector<Plate*>&plates, QSqlDatabase db)
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

