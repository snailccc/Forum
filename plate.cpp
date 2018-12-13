#include "plate.h"

//////////////////////Plate/////////////////////
Plate::Plate(int id, QString title,QWidget *parent):
    QPushButton (parent),id(id),title(title)
{
    this->setText(title);
    this->setStyleSheet("background-color: rgb(170, 0, 255);");
}

//void Plate::AddPost(Post *post)
//{
//   plateview->Add(post);
//}

//void Plate::DeletePost(int id)
//{
//    plateview->Delete(id);
//}

void Plate::Show()
{
    this->plateview = new PlateView(title,id,0);
    plateview->show();
}

int Plate::Id()
{
    return id;
}

//////////////////////PlateView/////////////////////
PlateView::PlateView(QString title,int id, QWidget *parent):
    QDialog(parent),title(title),plateId(id),
    ui(new Ui::Plate)
{
    ui->setupUi(this);
    this->setWindowTitle(title);
    this->setFixedSize(800,600);
    ui->plate_title->setText(title);

    ui->postGroup->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->postGroup->verticalHeader()->hide();
    ui->postGroup->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->postGroup->setContextMenuPolicy(Qt::CustomContextMenu);

    Init_View();
}

void PlateView::Init_View()
{
    QSqlQuery query(db);
    query.exec("select * from post where plateId="+QString::number(plateId));
    while(query.next())
    {
        int postId1 = query.value(0).toInt();
        QString title1 = query.value(1).toString();
        QString content1 = query.value(2).toString();
        QString authorId1 = query.value(3).toString();
        postgroup.insert(postgroup.begin(),new Post(postId1,plateId, title1, content1,authorId1));
    }
    int n = postgroup.size();
    ui->postGroup->setRowCount(n);
    for(int i=0;i<n;i++)
    {
        Post *post = postgroup[i];
        ui->postGroup->setCellWidget(i,0,post);
        connect(post,SIGNAL(clicked(bool)),this,SLOT(postDetail()));
    }
}

void PlateView::Add(Post *post){
    postgroup.insert(postgroup.begin(),post);
    ui->postGroup->insertRow(0);
    ui->postGroup->setCellWidget(0,0,postgroup.front());
    connect(postgroup.front(),SIGNAL(clicked(bool)),this,SLOT(postDetail()));
    update();

    QSqlQuery query(db);
    QString op = "insert into post values (";
    op += "\"" + QString::number(post->ID()) + "\",";
    op += "\"" + post->Title() + "\",";
    op += "\"" + post->Content() + "\",";
    op += "\"" + post->AuthorId() + "\",";
    op += "\"" + QString::number(post->PlateId()) + "\")";
    query.exec(op);
}

void PlateView::Delete(int postId)
{
    vector<Post*>::iterator it=postgroup.begin();
    int pos = postgroup.size();
    int index = 0;

    while(it!=postgroup.end())
    {
        Post *post = *it;
        if(post->ID() == postId)
        {

            ui->postGroup->removeRow(index);
            it = postgroup.erase(it);
            break;
        }
        else
        {
            index++;
            it++;
        }
    }
    update();

    QSqlQuery query(db);
    query.exec("delete from post where id="+QString::number(postId));
    query.exec("delete from comments where postId="+QString::number(postId));
}

void PlateView::on_pub_post_clicked(bool checked)
{
    pub_view = new PubView(this);
    pub_view->show();
    if(pub_view->exec()==QDialog::Accepted)
    {
        int id = postgroup.size()+this->plateId*1000+1;
        QString p_title = pub_view->Title();
        QString p_content = pub_view->Content();
        Post *post = new Post(id,plateId,p_title,p_content,user->ID());
        Add(post);
        update();
    }
}

void PlateView::postDetail()
{
    Post *post = qobject_cast<Post *>(sender());
    int postId = post->Show();
    if(postId)
    {
        Delete(postId);
    }
}

//////////////////////PubView/////////////////////
PubView::PubView(QWidget *parent):
    QDialog(parent),ui(new Ui::Public)
{
    ui->setupUi(this);
}

QString PubView::Title()
{
    return title;
}

QString PubView::Content()
{
    return content;
}

void PubView::on_ok_clicked(bool checked)
{
    title = ui->title->text();
    content = ui->content->toPlainText();
    accept();
}

//////////////////////Post_Mange_View/////////////////////

