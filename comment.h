#ifndef COMMENT_H
#define COMMENT_H

#include "global.h"
#include<QDateTime>
#include<QLabel>
#include<QPushButton>
#include<QObject>
#include<QTextBrowser>

class Comment;
class Del_Button;

/////////////////////////////Del_Button////////////////////////
class Del_Button:public QPushButton
{
    Q_OBJECT
private:
    QString id;
    QString text;
public:
    Del_Button(QString id,QString text,QWidget *parent=0);
    Del_Button();
    QString Id(){return id;}
};

/////////////////////////////Comment////////////////////////
class Comment:public QObject
{
    Q_OBJECT
private:
    QString content, authorId, authorName;
    QTextBrowser *contentView;
    int time, postId;
    QString id;
    Del_Button *del;
public:
    Comment(QString commentId, QString content,QString authorId, QString authorName, int postId);
    int PostId();
    QString Id();
    QPushButton* DelButton();
    QString AuthorId();
    QString AuthorName();
    QString Content();
    QTextBrowser* ContentView();
public slots:
    int Del();
};


#endif // COMMENT_H
