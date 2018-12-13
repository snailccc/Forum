#include "comment.h"

/////////////////////////////Del_Button////////////////////////
Del_Button::Del_Button(QString id, QString text, QWidget *parent):
    QPushButton (parent),id(id),text(text)
{
    this->setText(text);
}

/////////////////////////////Comment////////////////////////
Comment::Comment(QString commentId,QString content,QString authorId, QString authorName, int postId):
    id(commentId),content(content),authorId(authorId),authorName(authorName),postId(postId)
{
    contentView = new QTextBrowser();
    del = new Del_Button(id,"X");
    contentView->setText(content);
    QFont font;
    font.setPointSize(11);
    contentView->setFont(font);
}

QString Comment::Id()
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
    return 0;
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
