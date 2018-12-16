#include "post.h"

////////////////////////////////Post////////////////////////////////////////
Post::Post(int id,int plateId, QString title, QString content, QString authorId,QWidget *parent):
    QPushButton (parent),title(title),content(content),authorId(authorId),id(id),plateId(plateId)
{
    this->setText(title);
}

int Post::Show()
{
    this->view = new PostView(id,plateId,content,title,authorId);
    this->view->show();

    if(view->exec()==2)
    {
       return id;
    }
    return 0;
}

////////////////////////////////PostView////////////////////////////////////////
PostView::PostView(int postId, int plateId,QString postContent, QString postTitle,QString authorId,QWidget *parent):
    QDialog(parent),postId(postId),plateId(plateId),postContent(postContent),
    postTitle(postTitle),ui(new Ui::post),authorId(authorId)
{
    ui->setupUi(this);
    this->setWindowTitle(postTitle);
    ui->post_content->setText(this->postContent);
    delPost = new QPushButton("删除该贴", this);
    delPost->setGeometry(340,120,100,30);
    connect(delPost,SIGNAL(clicked(bool)),this,SLOT(DelPost()));

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
    if(user->ID()!=authorId && user->Type()!=MANAGER)
    {
        if(user->Type()==HOST_USER)
        {
            if(user->PlateId()!=plateId)
            {
                delPost->setVisible(0);
            }
        }
        else
        {
            delPost->setVisible(0);
        }
    }

    QString op = "select * from comments where postId="+QString::number(postId);
    commentGroup<<op;

    int n = commentGroup.size();
    ui->commentGroup->setRowCount(n);
    for(int i=0;i<n;i++)
    {
        Comment *comment = commentGroup[i];
        ui->commentGroup->setItem(i,0,new QTableWidgetItem(comment->AuthorName()));
        ui->commentGroup->setCellWidget(i,1,comment->ContentView());
        if(comment->AuthorId()==user->ID())
        {
            ui->commentGroup->setCellWidget(i,2,comment->DelButton());
            connect(comment->DelButton(),SIGNAL(clicked(bool)),this,SLOT(DelComment()));
        }

    }
}

void PostView::AddComment(QString commentId, QString content, QString authorId, QString authorName, int postId1)
{    
    Comment *comment = new Comment(commentId,content,authorId,authorName,postId1);
    commentGroup.insert(commentGroup.begin(),comment);
    ui->commentGroup->insertRow(0);
    ui->commentGroup->setItem(0,0,new QTableWidgetItem(user->Name()));
    ui->commentGroup->setCellWidget(0,1,comment->ContentView());
    if(comment->AuthorId()==user->ID())
    {
        ui->commentGroup->setCellWidget(0,2,comment->DelButton());
        connect(comment->DelButton(),SIGNAL(clicked(bool)),this,SLOT(DelComment()));
    }

    comment>>db;
}

void PostView::on_add_clicked(bool checked)
{
    if(user->Type()==ANONYMOUS)
    {
        QMessageBox::warning(0,tr("warning"),tr("please login first"));
        return;
    }
    pubComment = new PubComment(this);
    pubComment->show();
    if(pubComment->exec() == QDialog::Accepted)
    {
        QString c_content = pubComment->Content();
        QString id = QString::number(postId)+"_c_"+QString::number(commentGroup.size());
        AddComment(id, c_content, user->ID(),user->Name(),postId);
        update();
    }
}

void PostView::DelComment()
{
    Del_Button *button = qobject_cast<Del_Button*>(sender());
    QString commentId = button->Id();
    vector<Comment*>::iterator it=commentGroup.begin();

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

    QSqlQuery query(db);
    query.prepare("DELETE from comments where id=?");
    query.addBindValue(commentId);
    if(!query.exec())
    {
        QMessageBox::warning(0,QObject::tr("database connect error"),QObject::tr("please check your internet connect and database"));
        exit(0);
    }

    update();
}

void PostView::DelPost()
{
    if(this->commentGroup.size()==0&&this->authorId==user->ID())
    {
        done(2);
        return;
    }
    if(user->Type()==HOST_USER)
    {
        if(user->PlateId()==plateId)
        {
            done(2);
            return;
        }
    }
    if(user->Type()==MANAGER)
    {
        done(2);
        return;
    }
    QMessageBox::warning(this,tr("warning"),tr("删除失败"),QMessageBox::Yes);
}

vector<Comment*>& operator<< (vector<Comment*>& group, QString op)
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

Comment*& operator>> (Comment*& comment, QSqlDatabase db)
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
