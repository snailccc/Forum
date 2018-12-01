#ifndef POST_H
#define POST_H
#include "header.h"
#include "user.h"
#include "comment.h"
#include "ui_post.h"
#include "ui_comment.h"
#include<QDateTime>
#include<QAbstractListModel>
#include<QStringList>
#include<QObject>
#include<QVariant>
#include<QPushButton>
#include<QTextEdit>
#include<QSpacerItem>

class Post;
class PostView;
class PubComment;

////////////////////////////////Post////////////////////////////////////////
class Post:public QPushButton
{
    Q_OBJECT
private:
    QString title,content,authorId;
    int timestamp, id;
    PostView *view;

public:
    Post(QWidget *parent, int id, QString title, QString content, QString authorId);
    Q_INVOKABLE QString Title()const{return title;}
    Q_INVOKABLE int ID()const{return id;}
    Q_INVOKABLE QString Content()const{return content;}
    int Show();
    void AddComment(int commentId, QString content);

};

////////////////////////////////PostView////////////////////////////////////////

class PostView:public QDialog
{
    Q_OBJECT
private:
    Ui::post *ui;
    vector<Comment*>commentGroup;
    QString postContent,postTitle,authorId;
    int postId;
    PubComment *pubComment;
public:
    PostView(QWidget *parent,int postId, QString postContent,QString postTitle,QString authorId);
    void Init_View();
    void AddComment(int commentId, QString content);

private slots:
    void on_add_clicked(bool checked);
    void DelPost();
    void DelComment();
};

////////////////////////////////PubComment////////////////////////////////////////
class PubComment:public QDialog
{
    Q_OBJECT
private:
    Ui::comment *ui;
    QString content;
public:
    PubComment(QWidget *parent);
    QString Content();
private slots:
    void on_choice_accepted();

};

////////////////////////////////PostGroup////////////////////////////////////////

//class PostGroup:public QAbstractListModel
//{
//public:
//    enum PostRoles {
//        TitleRole = Qt::UserRole + 1,
//        ContentRole,
//        IDRole
//    };

//    PostGroup(QObject *parent = 0);

//    void AddPost(const Post &post);

//    int rowCount(const QModelIndex & parent = QModelIndex()) const;

//    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

//protected:
//    QHash<int, QByteArray> roleNames() const;
//private:
//    QList<Post>group;
//    QString title;
//};

#endif // POST_H
