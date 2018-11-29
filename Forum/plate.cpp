#include "plate.h"

Plate::Plate(QWidget *parent, int id, QString title):
    QPushButton(parent),id(id),title(title)
{
    this->setText(title);
    postgroup = new PostGroup;
}

