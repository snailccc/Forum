#include "plate.h"

//Post *test[2]={
//    new Post(NULL,100001,"post_test1","fox test"),
//    new Post(NULL,100002,"post_test2","fox test")
//};

Plate::Plate(QWidget *parent, int id, QString title):
    QPushButton(parent),id(id),title(title)
{
    this->setText(title);
    this->view = new Plate_View(this,title);
}

void Plate::AddPost(Post *post)
{
    view->Add(post);
}

void Plate::DeletePost(int id)
{
    view->Delete();
}

void Plate::Show()
{
    view->Init_View();
    view->show();
}


//////////////////////Plate_View/////////////////////
Plate_View::Plate_View(QWidget *parent,QString title):
    QDialog(parent),title(title),
    ui(new Ui::Plate)
{

}

void Plate_View::Init_View()
{
    ui->setupUi(this);
    this->setWindowTitle(title);
    this->setFixedSize(800,600);
    for(int i=postgroup.size()-1;i>=0;i--)
    {
        Post *post = postgroup[i];
        ui->post_group->addWidget(post);
    }
}

void Plate_View::Add(Post *post){
    postgroup.push_back(post);
}

void Plate_View::Delete()
{

}
