#include "comment.h"

Comment::Comment(QWidget *parent,int commentId,QString content,QString authorId):
    QObject(parent),id(commentId),content(content),authorId(authorId)
{
    view = new QLabel(content,0);
    del = new Del_Button(0,id,"X");
    view->setAlignment(Qt::AlignVCenter);
    view->setStyleSheet("QLabel{background:yellow}");
    QFont font;
    font.setPointSize(11);
    view->setFont(font);
}

int Comment::Id()
{
    return id;
}

QLabel* Comment::View()
{
    return view;
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
