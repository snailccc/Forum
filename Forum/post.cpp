#include "post.h"

////////////////////////////////Post///////////////////////////////////////////////
Post::Post(QWidget *parent, int id, int plateId,QString title, QString content, QString authorId):
    QPushButton(parent), id(id),plateId(plateId),title(title),content(content),authorId(authorId)
{
    this->setText(title);
    this->view = new PostView(this,id,plateId,content,title,authorId);
}

int Post::Show()
{
    this->view->Init_View();
    this->view->show();
    if(view->exec()==2)
    {
       return id;
    }
    return 0;
}

void Post::AddComment(int commentId,QString content,QString authorId, QString authorName)
{
    view->AddComment(commentId,content, authorId, authorName);
}

////////////////////////////////PostView///////////////////////////////////////////////
PostView::PostView(QWidget *parent, int postId, int plateId,QString postContent, QString postTitle,QString authorId):
    QDialog(parent),postId(postId),plateId(plateId),postContent(postContent),
    postTitle(postTitle),ui(new Ui::post),authorId(authorId)
{
    ui->setupUi(this);
    this->setWindowTitle(postTitle);
    ui->post_content->setText(this->postContent);
    delPost = new QPushButton("删除该贴", this);
    delPost->setGeometry(340,120,100,30);
    connect(delPost,SIGNAL(clicked(bool)),this,SLOT(DelPost()));


    this->commentGroup.push_back(new Comment(0,postId+commentGroup.size(),"justfortest1", "u1","fox1"));
    this->commentGroup.push_back(new Comment(0,postId+commentGroup.size(),"justfortest1", "u2","fox2"));
    this->commentGroup.push_back(new Comment(0,postId+commentGroup.size(),"justfortest1", "u3","fox3"));

    ui->commentGroup->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    ui->commentGroup->setColumnWidth(0,100);
    ui->commentGroup->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->commentGroup->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);
    ui->commentGroup->setColumnWidth(2,50);
    ui->commentGroup->verticalHeader()->hide();
    ui->commentGroup->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->commentGroup->setContextMenuPolicy(Qt::CustomContextMenu);


}

void PostView::Init_View()
{
    if(!(user->ID() == authorId ||
            user->Type()==MANAGER_USER ||
            (user->Type()==HOST_USER && user->PlateId()==this->plateId)))
    {
        delPost->hide();
    }
    else
    {
        delPost->show();
    }

//    ui->commentGroup->setSettionResizeMode(0,QHeaderView::Fixed);

    ui->commentGroup->clearContents();
    ui->commentGroup->setRowCount(commentGroup.size());
    for(int i=0;i<commentGroup.size();i++)
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

void PostView::AddComment(int commentId,QString content,QString authorId, QString authorName)
{
    Comment *comment = new Comment(this,commentId,content,authorId,authorName);
    commentGroup.insert(commentGroup.begin(),comment);
    ui->commentGroup->insertRow(0);
    ui->commentGroup->setItem(0,0,new QTableWidgetItem(user->Name()));
    ui->commentGroup->setCellWidget(0,1,comment->ContentView());
    if(comment->AuthorId()==user->ID())
    {
        ui->commentGroup->setCellWidget(0,2,comment->DelButton());
        connect(comment->DelButton(),SIGNAL(clicked(bool)),this,SLOT(DelComment()));
    }


}

void PostView::on_add_clicked(bool checked)
{
    pubComment = new PubComment(this);
    pubComment->show();
    if(pubComment->exec() == QDialog::Accepted)
    {
        QString c_content = pubComment->Content();
        int id = postId*1000 + commentGroup.size();
        AddComment(id, c_content, user->ID(),user->Name());
        update();
    }
}

void PostView::DelComment()
{
    Del_Button *button = qobject_cast<Del_Button*>(sender());
    int commentId = button->Id();
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
    update();
}

void PostView::DelPost()
{
    done(2);
}

////////////////////////////////PostGroup///////////////////////////////////////////////
PubComment::PubComment(QWidget *parent):
    ui(new Ui::comment)
{
    ui->setupUi(this);
    this->setWindowTitle("comment");
}

void PubComment::on_choice_accepted()
{
    content = ui->content->toPlainText();
}

QString PubComment::Content()
{
    return content;
}

////////////////////////////////PostGroup///////////////////////////////////////////////
//PostGroup::PostGroup(QObject *parent)
//    : QAbstractListModel(parent)
//{
//}

//void PostGroup::AddPost(const Post &post)
//{
//    beginInsertRows(QModelIndex(), rowCount(), rowCount());
//    group << post;
//    endInsertRows();
//}

//int PostGroup::rowCount(const QModelIndex & parent) const {
//    Q_UNUSED(parent);
//    return group.count();
//}

//QVariant PostGroup::data(const QModelIndex & index, int role) const {
//    if (index.row() < 0 || index.row() >= group.count())
//        return QVariant();

//    const Post &post = group[index.row()];
//    if (role == TitleRole)
//        return post.Title();
//    else if (role == ContentRole)
//        return post.Content();
//    else if (role == IDRole)
//        return post.Id();
//    return QVariant();
//}

//QHash<int, QByteArray> PostGroup::roleNames() const {
//    QHash<int, QByteArray> roles;
//    roles[TitleRole] = "title";
//    roles[ContentRole] = "content";
//    roles[IDRole] = "id";
//    return roles;
//}


