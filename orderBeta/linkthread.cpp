#include "linkthread.h"
#include <QEventLoop>

linkthread::linkthread(MainWindow *w,QObject *parent) : QThread(parent)
{
    //l.moveToThread(this);
    connect(w,SIGNAL(sendlink(QString)),&l,SLOT(writetohost(QString)));
    connect(w,SIGNAL(sendlogin()),&l,SLOT(login()));
    connect(w,SIGNAL(senddata()),&l,SLOT(datatohost()));
    connect(&l,SIGNAL(sendError(QString)),w,SLOT(showError(QString)));
}
linkthread::~linkthread()
{
    this->quit();
    this->wait();
}
void linkthread::run()
{
    //qDebug()<<"link ThreadId"<<QThread::currentThreadId();
    exec();
}
