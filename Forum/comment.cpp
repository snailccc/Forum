#include "comment.h"

Comment::Comment(QWidget *parent,QString content):
    QLabel(parent),content(content)
{
    this->setText(content);
    this->setAlignment(Qt::AlignVCenter);
    this->setStyleSheet("QLabel{background:yellow}");
}
