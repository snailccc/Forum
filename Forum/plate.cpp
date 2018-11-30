#include "plate.h"

//////////////////////Plate/////////////////////
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
//    connect(test,SIGNAL(clicked(bool)),this,SLOT(Pub_Post()));
}

void Plate_View::Init_View()
{
    ui->setupUi(this);
    this->setWindowTitle(title);
    this->setFixedSize(800,600);
    for(int i=postgroup.size()-1;i>=0;i--)
    {
        Post *post = postgroup[i];
        ui->postgroup->addWidget(post,1);
        connect(post,SIGNAL(clicked(bool)),this,SLOT(postDetail()));
    }
}

void Plate_View::Add(Post *post){
    postgroup.push_back(post);
}

void Plate_View::Delete()
{

}

void Plate_View::on_pub_post_clicked(bool checked)
{
    pub_view = new Pub_View(this);
    pub_view->show();
    if(pub_view->exec()==QDialog::Accepted)
    {
        int id = 100007;
        QString p_title = pub_view->Title();
        QString p_content = pub_view->Content();
        Post *post = new Post(0,id,p_title,p_content);
        postgroup.insert(postgroup.begin(),post);
        ui->postgroup->addWidget(postgroup.front());
        update();
    }
}

void Plate_View::postDetail()
{
    qDebug()<<"detail"<<endl;
}

//////////////////////Pub_View/////////////////////
Pub_View::Pub_View(QWidget *parent):
    QDialog(parent),ui(new Ui::Public)
{
    ui->setupUi(this);
}

QString Pub_View::Title()
{
    return title;
}

QString Pub_View::Content()
{
    return content;
}

void Pub_View::on_ok_clicked(bool checked)
{
    title = ui->title->text();
    content = ui->content->toPlainText();
    accept();
}
