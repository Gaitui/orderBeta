#include "linkthread.h"
#include <QEventLoop>

linkthread::linkthread(MainWindow *w,QObject *parent) : QThread(parent)
{
    connect(w,SIGNAL(sendlink(QString)),&l,SLOT(writetohost(QString)));
    connect(w,SIGNAL(sendlogin()),&l,SLOT(login()));
    connect(w,SIGNAL(senddata()),&l,SLOT(datatohost()));
    connect(&l,SIGNAL(sendError(QString)),w,SLOT(showError(QString)));
    connect(&l,SIGNAL(relogin()),w,SLOT(relogin()));
    connect(&l,SIGNAL(fromtcp()),w,SLOT(fromtcp()));
    connect(&l,SIGNAL(serverfail(QString)),w,SLOT(serverfail(QString)));
}
linkthread::~linkthread()
{
    this->quit();
    this->wait();
}
void linkthread::run()
{
    exec();
}
