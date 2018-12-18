#include "plate.h"

//////////////////////Plate/////////////////////
Plate::Plate(int id, QString title,QWidget *parent):
    QPushButton (parent),id(id),title(title)
{
    this->setText(title);
    this->setStyleSheet("background-color: rgb(196, 226, 216);");
}

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
    //初始化窗口信息
    ui->setupUi(this);
    this->setWindowTitle(title);
    ui->plate_title->setText(title);
    ui->plate_title->setStyleSheet("color:white");
    //载入背景图片
    QPalette palette;
    QPixmap pixmap(":/img/bg1");
    palette.setBrush(QPalette::Window,QBrush(pixmap.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    this->setPalette(palette);
    //设置帖子列表属性
    ui->postGroup->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->postGroup->verticalHeader()->hide();
    ui->postGroup->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->postGroup->setContextMenuPolicy(Qt::CustomContextMenu);

    Init_View();//初始化界面
}

void PlateView::Init_View()
{
    //插入帖子，初始化帖子列表
    QString op = "select * from post where plateId="+QString::number(plateId);
    postgroup<<op;
    int n = postgroup.size();
    ui->postGroup->setRowCount(n);
    for(int i=0;i<n;i++)
    {
        Post *post = postgroup[i];
        ui->postGroup->setCellWidget(i,0,post);
        connect(post,SIGNAL(clicked(bool)),this,SLOT(postDetail()));
    }
}

void PlateView::Add(Post *post)//插入帖子
{
    postgroup.insert(postgroup.begin(),post);
    ui->postGroup->insertRow(0);
    ui->postGroup->setCellWidget(0,0,postgroup.front());
    connect(postgroup.front(),SIGNAL(clicked(bool)),this,SLOT(postDetail()));
    update();
    post>>db;
}

void PlateView::Delete(int postId)//删除帖子
{
    vector<Post*>::iterator it=postgroup.begin();
    int pos = postgroup.size();
    int index = 0;
    //遍历帖子容器，找到对应帖子进行删除
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
    if(!query.exec("delete from post where id="+QString::number(postId)))
    {
        QMessageBox::warning(0,QObject::tr("database connect error"),QObject::tr("please check your internet connect and database"));
        exit(0);
    }
    if(!query.exec("delete from comments where postId="+QString::number(postId)))
    {
        QMessageBox::warning(0,QObject::tr("database connect error"),QObject::tr("please check your internet connect and database"));
        exit(0);
    }
}

void PlateView::on_pub_post_clicked(bool checked)//打开帖子发布窗口
{
    if(user->Type()==ANONYMOUS)
    {
        QMessageBox::warning(0,tr("warning"),tr("please login first"));
        return;
    }
    pub_view = new PubView(this);
    pub_view->show();
    //成功后向容器插入帖子
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

void PlateView::postDetail()//打开帖子界面
{
    Post *post = qobject_cast<Post *>(sender());
    int postId = post->Show();
    if(postId)
    {
        Delete(postId);
    }
}

vector<Post*>& operator<<(vector<Post*>& group, QString op)//重载从数据库中导入所有数据
{
    QSqlQuery query(db);
    if(!query.exec(op))
    {
        QMessageBox::warning(0,QObject::tr("database connect error"),QObject::tr("please check your internet connect and database"));
        exit(0);
    }
    while(query.next())
    {
        int postId1 = query.value(0).toInt();
        QString title1 = query.value(1).toString();
        QString content1 = query.value(2).toString();
        QString authorId1 = query.value(3).toString();
        int plateId1 = query.value(4).toInt();
        group.insert(group.begin(),new Post(postId1,plateId1, title1, content1,authorId1));
    }
    return group;
}

Post*& operator>>(Post*& post1, QSqlDatabase db)//重载向数据库插入帖子
{
    QSqlQuery query(db);
    query.prepare("insert into post (id,title,content,authorId,plateId) values (?,?,?,?,?)");
    query.addBindValue(post1->ID());
    query.addBindValue(post1->Title());
    query.addBindValue(post1->Content());
    query.addBindValue(post1->AuthorId());
    query.addBindValue(post1->PlateId());
    if(!query.exec())
    {
        QMessageBox::warning(0,QObject::tr("database connect error"),QObject::tr("please check your internet connect and database"));
        exit(0);
    }
    return post1;
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

void PubView::on_ok_clicked(bool checked)//发布成功
{
    title = ui->title->text();
    content = ui->content->toPlainText();
    accept();
}

//////////////////////Post_Mange_View/////////////////////

