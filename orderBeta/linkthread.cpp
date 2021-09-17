#include "linkthread.h"
#include <QEventLoop>

linkthread::linkthread(MainWindow *w,QObject *parent) : QThread(parent)
{
    l.moveToThread(this);
    connect(w,SIGNAL(sendlink(QString)),&l,SLOT(writetohost(QString)));
}
linkthread::~linkthread()
{
    this->quit();
    this->wait();
}
void linkthread::run()
{
    l.waitForBytesWritten();

    //delete l;
    exec();
}
