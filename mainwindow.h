#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDateTime>
#include <QStringList>

#include "post.h"
#include "comment.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    qint64 totalBytes;
    qint64 bytesReceived;
    qint64 bytestoWrite;
    qint64 bytesWritten;

    qint64 perDataSize;
    QByteArray inBlock;
    QByteArray outBlock;

    QDateTime current_data_time;
    QString str_data_time;

    vector<QTcpSocket*>socketgroup;
public:
    QTcpServer *server;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void AddComment(QStringList segs);
    void DelComment(QString commentId);
    void AddPost(QStringList segs);
    void DelPost(QStringList segs);
    void Appoint(QStringList segs);
    void Remove(QStringList segs);
    void sendMessage(QString Message);
    friend Comment*& operator>>(Comment*& comment, QSqlDatabase);
    friend Post*& operator>>(Post*& post1,QSqlDatabase db);
    friend Base& operator >>(Base& base, QSqlDatabase db);
private slots:
    void on_newClient_clicked(bool checked);
    void acceptConnection();
    void receiveData();
    void displayError(QAbstractSocket::SocketError socketError);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
