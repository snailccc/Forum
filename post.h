#ifndef POST_H
#define POST_H

#include "global.h"
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
#include<QTableWidget>
#include<QTableWidgetItem>
#include<QTextBrowser>

class Post;
class PostView;
class PubComment;

////////////////////////////////Post////////////////////////////////////////
class Post:public QPushButton
{
    Q_OBJECT
private:
    QString title,content,authorId;
    int timestamp, id, plateId;
    PostView *view;
public:
    Post(int id,int plateId, QString title, QString content, QString authorId,QWidget *parent=0);
    QString Title()const{return title;}
    QString Content()const{return content;}
    QString AuthorId()const{return authorId;}
    int ID()const{return id;}
    int PlateId()const{return plateId;}
    int Show();
    void AddComment(QString commentId, QString content, QString authorId, QString authorName, int postId1);
};

////////////////////////////////PostView////////////////////////////////////////
class PostView:public QDialog
{
    Q_OBJECT
private:
    Ui::post *ui;
    QString postContent,postTitle,authorId;
    int postId,plateId;
    PubComment *pubComment;
    QPushButton *delPost;
    vector<Comment*>commentGroup;
public:
    PostView(int postId, int plateId,QString postContent,QString postTitle,QString authorId,QWidget *parent=0);
    void Init_View();
    void AddComment(QString commentId, QString content, QString authorId,QString authorName, int postId);
    int ComentSize(){return ui->commentGroup->rowCount();}
    friend vector<Comment*>& operator<<(vector<Comment*>& group, QString op);
    friend Comment*& operator>>(Comment*& comment, QSqlDatabase);
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
    PubComment(QWidget *parent=0);
    QString Content();
private slots:
    void on_choice_accepted();

};
#endif // POST_H
