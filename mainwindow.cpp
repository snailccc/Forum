#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "global.h"
#include "client.h"

extern vector<User*>clients;
extern map<QString, Base> userGroup;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server = new QTcpServer(this);
    server->listen(QHostAddress::Any,666);
    connect(server,SIGNAL(newConnection()),this,SLOT(acceptConnection()));

    bytesReceived = 0;
    totalBytes = 0;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddComment(QStringList segs)
{
    current_data_time = QDateTime::currentDateTime();
    str_data_time = current_data_time.toString("yyyy-MM-dd hh:mm:ss")+"\n";
    QString commentId = segs[0];
    QString commentContent = segs[1];
    QString authorId = segs[2];
    QString authorName = segs[3];
    int postId = segs[4].toInt();
    Comment *comment = new Comment(commentId,commentContent,authorId,authorName,postId);
    comment>>db;
    QString str = str_data_time+"user " +authorId+ " pub comment: " + commentContent;
    ui->serverDisplay->append(str);
}

void MainWindow::DelComment(QString commentId)
{
    current_data_time = QDateTime::currentDateTime();
    str_data_time = current_data_time.toString("yyyy-MM-dd hh:mm:ss")+"\n";
    QSqlQuery query(db);
    query.prepare("DELETE from comments where id=?");
    query.addBindValue(commentId);
    if(!query.exec())
    {
        QMessageBox::warning(0,QObject::tr("database connect error"),QObject::tr("please check your internet connect and database"));
        exit(0);
    }
    QString str = str_data_time+"post "+commentId+" is deleted by its author";
    ui->serverDisplay->append(str);
}

void MainWindow::AddPost(QStringList segs)
{
    current_data_time = QDateTime::currentDateTime();
    str_data_time = current_data_time.toString("yyyy-MM-dd hh:mm:ss")+"\n";
    QString postId = segs[0];
    QString postTitle = segs[1];
    QString postContent = segs[2];
    QString authorId = segs[3];
    QString plateId = segs[4];
    Post *post = new Post(postId.toInt(),plateId.toInt(),postTitle,postContent,authorId);
    post>>db;
    QString str = str_data_time+"user " +authorId+ " pub post: " + postTitle + "(" + postId + ")";
    ui->serverDisplay->append(str);
}

void MainWindow::DelPost(QStringList segs)
{
    current_data_time = QDateTime::currentDateTime();
    str_data_time = current_data_time.toString("yyyy-MM-dd hh:mm:ss")+"\n";
    QString postId = segs[0];
    QString userId = segs[1];

    QSqlQuery query(db);
    if(!query.exec("delete from post where id="+postId))
    {
        QMessageBox::warning(0,QObject::tr("database connect error"),QObject::tr("please check your internet connect and database"));
        exit(0);
    }
    if(!query.exec("delete from comments where postId="+postId))
    {
        QMessageBox::warning(0,QObject::tr("database connect error"),QObject::tr("please check your internet connect and database"));
        exit(0);
    }

    QString str = str_data_time+"post "+postId+" is deleted by user " + userId;
    ui->serverDisplay->append(str);
}

void MainWindow::Appoint(QStringList segs)
{
    QString userId = segs[0];
    QString plateId = segs[1];
    QString managerId = segs[2];
    Base base(userId,"","",HOST_USER,plateId.toInt());
    base>>db;

    current_data_time = QDateTime::currentDateTime();
    str_data_time = current_data_time.toString("yyyy-MM-dd hh:mm:ss")+"\n";
    QString str = str_data_time+"user " +userId+ " is pointed as the hoster of plate " + plateId + " by manager " + managerId;
    ui->serverDisplay->append(str);
}

void MainWindow::Remove(QStringList segs)
{
    QString userId = segs[0];
    QString managerId = segs[1];
    Base base(userId,"","",COMMENT_USER);
    base>>db;

    current_data_time = QDateTime::currentDateTime();
    str_data_time = current_data_time.toString("yyyy-MM-dd hh:mm:ss")+"\n";
    QString str = str_data_time+"user " +userId+ " is remove the hoster by manager " + managerId;
    ui->serverDisplay->append(str);
}

Post*& operator>>(Post*& post1, QSqlDatabase db)//重载向数据库插入帖子
{
    QSqlQuery query(db);
    query.prepare("insert into post (id,title,content,authorId,plateId) values (?,?,?,?,?)");
    query.addBindValue(post1->ID());
    query.addBindValue(post1->Title());
    query.addBindValue(post1->Content());
    query.addBindValue(post1->AuthorId());
    query.addBindValue(post1->PlateId());
    if(!query.exec())
    {
        QMessageBox::warning(0,QObject::tr("database connect error"),QObject::tr("please check your internet connect and database"));
        exit(0);
    }
    return post1;
}

Comment*& operator>> (Comment*& comment, QSqlDatabase db)//重载运算符，向数据库插入新的评论
{
    QSqlQuery query(db);
    query.prepare("insert into comments (id,content,authorId,authorName,postId) values (?,?,?,?,?)");
    query.addBindValue(comment->Id());
    query.addBindValue(comment->Content());
    query.addBindValue(comment->AuthorId());
    query.addBindValue(comment->AuthorName());
    query.addBindValue(comment->PostId());
    if(!query.exec())
    {
        QMessageBox::warning(0,QObject::tr("database connect error"),QObject::tr("please check your internet connect and database"));
        exit(0);
    }
    return comment;
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

void MainWindow::on_newClient_clicked(bool checked)
{
    LoginView *login = new LoginView();
    if(login->exec()==QDialog::Accepted)
    {
        Client *client = new Client(clients.size()-1);
        client->show();
    }
}

void MainWindow::acceptConnection()
{
    socketgroup.push_back(server->nextPendingConnection());
    connect(socketgroup[socketgroup.size()-1],SIGNAL(readyRead()),this,SLOT(receiveData()));
    connect(socketgroup[socketgroup.size()-1],SIGNAL(disconnected()),this,SLOT(DelSocket()));
    qDebug()<<"socket status:"<<endl;
    for(int i=0;i<socketgroup.size();i++)
    {
        qDebug()<<socketgroup[i]->state()<<endl;
    }
}

void MainWindow::sendMessage(QString message)
{
    for(int i=0;i<socketgroup.size();i++)
    {
        socketgroup[i]->write(message.toUtf8());
    }
}

void MainWindow::receiveData()
{
    for(int i=0;i<socketgroup.size();i++)
    {
        QString message = socketgroup[i]->readAll();
        if(message=="")continue;
        qDebug()<<"server:"<<message<<endl;
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
            Appoint(segs);
        }
        else if(op==op_remove)
        {
            Remove(segs);
        }
        sendMessage(message);
    }
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{

}

void MainWindow::DelSocket()
{
    for(vector<QTcpSocket*>::iterator it=socketgroup.begin();it!=socketgroup.end();)
    {
        QTcpSocket *socket = *it;
        if(socket->state()==QTcpSocket::UnconnectedState)
        {
            it = socketgroup.erase(it);
        }
        else
        {
            it++;
        }
    }
    qDebug()<<"socket status:"<<socketgroup.size()<<endl;
}
