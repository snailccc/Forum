#ifndef COMMENT_H
#define COMMENT_H
#include "header.h"
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
    int id;
    QString text;
public:
    Del_Button(QWidget *parent,int id,QString text):
        QPushButton(parent),id(id),text(text)
    {
        this->setText(text);
    }
    int Id(){return id;}
};

/////////////////////////////Comment////////////////////////
class Comment:public QObject
{
    Q_OBJECT
private:
    QString content, authorId, authorName;
    QTextBrowser *contentView;
    int time,id;
    Del_Button *del;
public:
    Comment(QWidget *parent,int commentId, QString content,QString authorId, QString authorName);
    int Id();
    QPushButton* DelButton();
    QString AuthorId();
    QString AuthorName();
    QString Content();
    QTextBrowser* ContentView();
public slots:
    int Del();
};

#endif // COMMENT_H
