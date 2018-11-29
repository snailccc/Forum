#include "plate.h"

Plate::Plate(QWidget *parent, int id, string title):
    QPushButton(parent)
{
    this->setText(QString::fromStdString(title));
    this->id = id;
    this->title = title;
}

