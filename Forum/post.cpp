#include "post.h"

////////////////////////////////Post///////////////////////////////////////////////
Post::Post(QWidget *parent, int id, QString title, QString content, QString authorId):
    QPushButton(parent), id(id),title(title),content(content),authorId(authorId)
{
    this->setText(title);
    this->view = new PostView(this,id,content,title,authorId);
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

void Post::AddComment(int commentId,QString content)
{
    view->AddComment(commentId,content);
}

////////////////////////////////PostView///////////////////////////////////////////////
PostView::PostView(QWidget *parent, int postId, QString postContent, QString postTitle,QString authorId):
    QDialog(parent),postId(postId),postContent(postContent),
    postTitle(postTitle),ui(new Ui::post),authorId(authorId)
{
    ui->setupUi(this);
    this->setWindowTitle(postTitle);
    ui->post_content->setText(this->postContent);
    if(user->ID() == authorId)
    {
        QPushButton *delPost = new QPushButton("删除该贴", this);
        delPost->setGeometry(340,120,100,30);
        connect(delPost,SIGNAL(clicked(bool)),this,SLOT(DelPost()));
    }
}

void PostView::Init_View()
{
    this->setWindowTitle(postTitle);
    for(int i=commentGroup.size()-1;i>=0;i++)
    {
        Comment *comment = commentGroup[i];
        ui->commentGroup->addWidget(comment->View());
        if(comment->AuthorId()==authorId)
        {
            ui->deleteButtonGroup->addWidget(comment->DelButton());
            connect(comment->DelButton(),SIGNAL(clicked(bool)),this,SLOT(DelComment()));
        }
        else
        {
            ui->deleteButtonGroup->addSpacing(20);
        }
    }
}

void PostView::AddComment(int commentId,QString content)
{
    Comment *comment = new Comment(this,commentId,content,user->ID());
    commentGroup.insert(commentGroup.begin(),comment);
}

void PostView::on_add_clicked(bool checked)
{
    pubComment = new PubComment(this);
    pubComment->show();
    if(pubComment->exec() == QDialog::Accepted)
    {
        QString c_content = pubComment->Content();
        Comment *comment = new Comment(this,123123,c_content,user->ID());
        commentGroup.insert(commentGroup.begin(),comment);
        comment = commentGroup.front();
        ui->commentGroup->addWidget(comment->View());
        ui->deleteButtonGroup->addWidget(comment->DelButton());
        connect(comment->DelButton(),SIGNAL(clicked(bool)),this,SLOT(DelComment()));
        update();
    }
}

void PostView::DelComment()
{
    Del_Button *button = qobject_cast<Del_Button*>(sender());
    int commentId = button->Id();
    vector<Comment*>::iterator it=commentGroup.begin();
    while(it!=commentGroup.end())
    {
        Comment *comment = *it;
        if(comment->Id() == commentId)
        {
            QLabel *view = comment->View();
            QPushButton *del = comment->DelButton();
            ui->commentGroup->removeWidget(view);
            ui->deleteButtonGroup->removeWidget(del);
            it = commentGroup.erase(it);
            break;
        }
        else
        {
            it++;
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


