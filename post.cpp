#include "post.h"

extern vector<User*>clients;
////////////////////////////////Post////////////////////////////////////////
Post::Post(int id,int plateId, QString title, QString content, QString authorId,QWidget *parent):
    QPushButton (parent),title(title),content(content),authorId(authorId),id(id),plateId(plateId)
{
    this->setText(title);
}

int Post::Show(int index,QTcpServer *server,QTcpSocket *socket)
{
    this->view = new PostView(index,id,plateId,content,title,authorId,server,socket);
    view->setModal(false);
    view->show();
    if(view->exec()==2)
    {
       return id;
    }
    delete(view);
    return 0;
}

////////////////////////////////PostView////////////////////////////////////////
PostView::PostView(int index, int postId, int plateId,QString postContent, QString postTitle,QString authorId,QTcpServer *server,QTcpSocket *socket,QWidget *parent):
    QDialog(parent),postId(postId),plateId(plateId),postContent(postContent),
    postTitle(postTitle),ui(new Ui::post),authorId(authorId),index(index),
    server(server),socket(socket)
{
    //初始化网络连接
    connect(socket,SIGNAL(readyRead()),this,SLOT(receiveData()));

    perDataSize = 64*1024;
    bytesWrite = 0;
    bytesWritten = 0;
    bytesRecived = 0;
    //初始化帖子界面
    ui->setupUi(this);
    this->setWindowTitle(postTitle);
    //初始化背景图
    QPalette palette;
    QPixmap pixmap(":/img/bg1");
    palette.setBrush(QPalette::Window,QBrush(pixmap));
    this->setPalette(palette);

    ui->post_content->setText(this->postContent);
    delPost = new QPushButton("删除该贴", this);
    delPost->setGeometry(340,120,100,30);
    connect(delPost,SIGNAL(clicked(bool)),this,SLOT(DelPost()));
    //初始化评论列表属性
    ui->commentGroup->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    ui->commentGroup->setColumnWidth(0,100);
    ui->commentGroup->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->commentGroup->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);
    ui->commentGroup->setColumnWidth(2,50);
    ui->commentGroup->verticalHeader()->hide();
    ui->commentGroup->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->commentGroup->setContextMenuPolicy(Qt::CustomContextMenu);

    Init_View();

}


void PostView::Init_View()
{
    //根据用户身份和信息显示帖子删除按钮
    if(clients[index]->ID()!=authorId && clients[index]->Type()!=MANAGER)
    {
        if(clients[index]->Type()==HOST_USER)
        {
            if(clients[index]->PlateId()!=plateId)
            {
                delPost->setVisible(0);
            }
        }
        else
        {
            delPost->setVisible(0);
        }
    }

    ui->commentGroup->setColumnWidth(2,50);
    QString op = "select * from comments where postId="+QString::number(postId);
    commentGroup<<op;
    //向评论列表插入评论
    int n = commentGroup.size();
    ui->commentGroup->setRowCount(n);
    for(int i=0;i<n;i++)
    {
        Comment *comment = commentGroup[i];
        ui->commentGroup->setItem(i,0,new QTableWidgetItem(comment->AuthorName()));
        ui->commentGroup->setCellWidget(i,1,comment->ContentView());
        if(comment->AuthorId()==clients[index]->ID())
        {
            ui->commentGroup->setCellWidget(i,2,comment->DelButton());
            connect(comment->DelButton(),SIGNAL(clicked(bool)),this,SLOT(on_del_comment()));
        }

    }
    update();
}

void PostView::sendData(QString message)
{
    socket->write(message.toUtf8());
}

void PostView::receiveData()
{
    QString message = socket->readAll();
    QStringList segs = message.split("|");
    int op = segs[0].toInt();
    segs.removeOne(segs.front());
    if(op==op_addcomment)
    {
        AddComment(segs[0],segs[1],segs[2],segs[3],segs[4].toInt());
    }
    else if(op==op_delcomment)
    {
        DelComment(segs[0]);
    }
}

void PostView::AddComment(QString commentId, QString content, QString authorId, QString authorName, int postId1)//新增评论
{
    Comment *comment = new Comment(commentId,content,authorId,authorName,postId1);
    commentGroup.insert(commentGroup.begin(),comment);
    ui->commentGroup->insertRow(0);
    ui->commentGroup->setItem(0,0,new QTableWidgetItem(clients[index]->Name()));
    ui->commentGroup->setCellWidget(0,1,comment->ContentView());
    if(comment->AuthorId()==clients[index]->ID())
    {
        qDebug()<<"add comment"<<content<<endl;
        ui->commentGroup->setCellWidget(0,2,comment->DelButton());
        connect(comment->DelButton(),SIGNAL(clicked(bool)),this,SLOT(on_del_comment()));
    }

}

void PostView::disconnectServer()
{
    socket->close();
}

void PostView::on_add_clicked(bool checked)//打开评论发布界面
{
    if(clients[index]->Type()==ANONYMOUS)
    {
        QMessageBox::warning(0,tr("warning"),tr("please login first"));
        return;
    }
    pubComment = new PubComment(this);
    if(pubComment->exec() == QDialog::Accepted)
    {
        QString c_content = pubComment->Content();
        QString id = QString::number(postId)+"_c_"+QString::number(commentGroup.size());

        QString message = QString::number(op_addcomment) + "|" +id + "|"+
                c_content + "|" + clients[index]->ID() +"|" +
                clients[index]->Name() + "|" + QString::number(postId);
        sendData(message);
    }
}

void PostView::on_del_comment()
{
    Del_Button *button = qobject_cast<Del_Button*>(sender());
    QString commentId = button->Id();
    QString message = QString::number(op_delcomment) + "|" +commentId;
    sendData(message);
}

void PostView::DelComment(QString commentId)//删除评论
{

    vector<Comment*>::iterator it=commentGroup.begin();
    //遍历评论容器，搜索目标评论，删除
    int pos = 0;
    while(it!=commentGroup.end())
    {
        Comment *comment = *it;
        if(comment->Id() == commentId)
        {

            ui->commentGroup->removeRow(pos);
            it = commentGroup.erase(it);
            break;
        }
        else
        {
            it++;
            pos++;
        }
    }
    update();
}

void PostView::DelPost()//删除帖子
{
    QString message = QString::number(op_delpost)+"|";
    if(this->commentGroup.size()==0&&this->authorId==clients[index]->ID())
    {
        message = message + QString::number(postId) + "|" + clients[index]->ID();
        sendData(message);
        done(2);
        return;
    }
    if(clients[index]->Type()==HOST_USER)
    {
        if(clients[index]->PlateId()==plateId)
        {
            message = message + QString::number(postId) + "|" + clients[index]->ID();
            sendData(message);
            done(2);
            return;
        }
    }
    if(clients[index]->Type()==MANAGER)
    {
        message = message + QString::number(postId) + "|" + clients[index]->ID();
        sendData(message);
        done(2);
        return;
    }
    QMessageBox::warning(this,tr("warning"),tr("删除失败"),QMessageBox::Yes);
}

vector<Comment*>& operator<< (vector<Comment*>& group, QString op)//重载运算符，从数据库导出评论数据
{
    QSqlQuery query(db);
    if(!query.exec(op))
    {
        QMessageBox::warning(0,QObject::tr("database connect error"),QObject::tr("please check your internet connect and database"));
        exit(0);
    }
    while(query.next())
    {
        QString commentId = query.value(0).toString();
        QString content = query.value(1).toString();
        QString authorId = query.value(2).toString();
        QString authorName = query.value(3).toString();
        int postId = query.value(4).toInt();
        group.insert(group.begin(),new Comment(commentId,content,authorId,authorName,postId));
    }
    return group;
}

////////////////////////////////PubComment////////////////////////////////////////
PubComment::PubComment(QWidget *parent):
    ui(new Ui::comment)
{
    ui->setupUi(this);
    this->setWindowTitle("comment");
}

void PubComment::on_choice_accepted()
{
    content = ui->content->toPlainText();
    accept();
}

QString PubComment::Content()
{
    return content;
}
