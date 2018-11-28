#include "plate.h"

Plate::Plate(QWidget *parent, int id, string title)
{
    this->setParent(parent);
    this->setText(QString::fromStdString(title));
    this->resize(10,10);
}
