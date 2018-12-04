#include "comment.h"

Comment::Comment(QWidget *parent,int commentId,QString content,QString authorId, QString authorName):
    QObject(parent),id(commentId),content(content),authorId(authorId),authorName(authorName)
{
    contentView = new QTextBrowser();
    del = new Del_Button(0,id,"X");
    contentView->setText(content);
    QFont font;
    font.setPointSize(11);
    contentView->setFont(font);
}

int Comment::Id()
{
    return id;
}


QPushButton* Comment::DelButton()
{
    return del;
}

QString Comment::AuthorId()
{
    return authorId;
}

int Comment::Del()
{

}

QString Comment::Content()
{
    return content;
}

QTextBrowser* Comment::ContentView()
{
    return contentView;
}

QString Comment::AuthorName()
{
    return authorName;
}
