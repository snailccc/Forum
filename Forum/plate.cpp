#include "plate.h"

//////////////////////Plate/////////////////////
Plate::Plate(QWidget *parent, int id, QString title):
    QPushButton(parent),id(id),title(title)
{
    this->setText(title);
    this->view = new Plate_View(this,title,id);
}

void Plate::AddPost(Post *post)
{
    view->Add(post);
}

void Plate::DeletePost(int id)
{
    view->Delete(id);
}

void Plate::Show()
{
    view->show();
}

int Plate::Id()
{
    return id;
}

//Plate_View* Plate::View()
//{
//    return view;
//}

//////////////////////Plate_View/////////////////////
Plate_View::Plate_View(QWidget *parent,QString title,int id):
    QDialog(parent),title(title),plateId(id),
    ui(new Ui::Plate)
{
    Init_View();
}

void Plate_View::Init_View()
{
    ui->setupUi(this);
    this->setWindowTitle(title);
    this->setFixedSize(800,600);
    for(int i=0;i<postgroup.size();i++)
    {
        Post *post = postgroup[i];
        ui->postgroup->addWidget(post,1);
        connect(post,SIGNAL(clicked(bool)),this,SLOT(postDetail()));
    }
}

void Plate_View::Add(Post *post){
    postgroup.insert(postgroup.begin(),post);
    ui->postgroup->insertWidget(0,postgroup.front());
    connect(postgroup.front(),SIGNAL(clicked(bool)),this,SLOT(postDetail()));
}

void Plate_View::Delete(int postId)
{
    vector<Post*>::iterator it=postgroup.begin();
    int pos = postgroup.size();
    while(it!=postgroup.end())
    {
        Post *post = *it;
        if(post->ID() == postId)
        {
            ui->postgroup->removeWidget(*it);
            it = postgroup.erase(it);
            break;
        }
        else
        {
            it++;
        }
    }
    update();
}

void Plate_View::on_pub_post_clicked(bool checked)
{
    pub_view = new Pub_View(this);
    pub_view->show();
    if(pub_view->exec()==QDialog::Accepted)
    {
        int id = postgroup.size()+this->plateId*1000+1;
        QString p_title = pub_view->Title();
        QString p_content = pub_view->Content();
        Post *post = new Post(this,id,plateId,p_title,p_content,user->ID());
        postgroup.insert(postgroup.begin(),post);
        ui->postgroup->insertWidget(0,postgroup.front());
        connect(postgroup.front(),SIGNAL(clicked(bool)),this,SLOT(postDetail()));
        update();
    }
}

void Plate_View::postDetail()
{
    Post *post = qobject_cast<Post *>(sender());
    int postId = post->Show();
    if(postId)
    {
        Delete(postId);
    }

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

//////////////////////Post_Mange_View/////////////////////

