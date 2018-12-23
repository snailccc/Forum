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
#include<QTcpServer>
#include<QTcpSocket>


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
    int Show(int index,QTcpServer *server,QTcpSocket *socket);
    void AddComment(QString commentId, QString content, QString authorId, QString authorName, int postId1);
};

////////////////////////////////PostView////////////////////////////////////////
class PostView:public QDialog
{
    Q_OBJECT
private:
    Ui::post *ui;
    QString postContent,postTitle,authorId;
    int postId,plateId,index;
    PubComment *pubComment;
    QPushButton *delPost;
    vector<Comment*>commentGroup;
    QTcpSocket *socket;
    QTcpServer *server;
    qint64 bytesWritten;
    qint64 bytesWrite;
    qint64 bytesRecived;
    qint64 perDataSize;
    QByteArray inBlock;
    QByteArray outBlock;

public:
    PostView(int index, int postId, int plateId,QString postContent,QString postTitle,QString authorId,QTcpServer *server,QTcpSocket *socket,QWidget *parent=0);
    void Init_View();
    void newConnect();
    void AddComment(QString commentId, QString content, QString authorId,QString authorName, int postId);
    int ComentSize(){return ui->commentGroup->rowCount();}
    friend vector<Comment*>& operator<<(vector<Comment*>& group, QString op);

private slots:
    void on_add_clicked(bool checked);
    void DelPost();
    void on_del_comment();
    void DelComment(QString commentId);
    void disconnectServer();
    void sendData(QString message);
    void receiveData();

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
