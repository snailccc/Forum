#include "post.h"

////////////////////////////////Post///////////////////////////////////////////////
Post::Post(QWidget *parent, int id, QString title, QString content, QString authorId):
    QPushButton(parent), id(id),title(title),content(content),authorId(authorId)
{
    this->setText(title);
    this->view = new PostView(this,id,content,title);
}

int Post::Show()
{
    this->view->show();
    if(view->exec()==2)
    {
       return id;
    }
    return 0;
}

void Post::AddComment(QString content)
{
    view->AddComment(content);
}

////////////////////////////////PostView///////////////////////////////////////////////
PostView::PostView(QWidget *parent, int postId, QString postContent, QString postTitle):
    QDialog(parent),postId(postId),postContent(postContent),postTitle(postTitle),ui(new Ui::post)
{
    ui->setupUi(this);
    this->setWindowTitle(postTitle);
    ui->post_content->setText(this->postContent);
    if(user->ID() == postId)
    {
        QPushButton *delPost = new QPushButton("删除该板块", this);
        delPost->setGeometry(340,120,100,30);
        connect(delPost,SIGNAL(clicked(bool)),this,SLOT(DelPost()));
    }
}

void PostView::Init_View()
{
    this->setWindowTitle(postTitle);
}

void PostView::AddComment(QString content)
{
    Comment *comment = new Comment(this,content);
    commentGroup.insert(commentGroup.begin(),comment);
}


void PostView::on_add_clicked(bool checked)
{
    pubComment = new PubComment(this);
    pubComment->show();
    if(pubComment->exec() == QDialog::Accepted)
    {
        QString c_content = pubComment->Content();
        Comment *comment = new Comment(this,c_content);
        commentGroup.insert(commentGroup.begin(),comment);
        ui->commentGroup->addWidget(commentGroup.front());
        update();
    }
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


