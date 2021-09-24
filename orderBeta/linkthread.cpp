#include "linkthread.h"
#include <QEventLoop>

linkthread::linkthread(MainWindow *w,outlog *lg,QObject *parent) : QThread(parent)
{
    connect(w,SIGNAL(sendlink(QString)),&l,SLOT(writetohost(QString)));
    connect(w,SIGNAL(sendlogin()),&l,SLOT(login()));
    connect(w,SIGNAL(senddata()),&l,SLOT(datatohost()));
    connect(&l,SIGNAL(sendError(QString)),w,SLOT(showError(QString)));
    connect(&l,SIGNAL(relogin()),w,SLOT(relogin()));
    connect(&l,SIGNAL(fromtcp()),w,SLOT(fromtcp()));
    connect(&l,SIGNAL(serverfail(QString)),w,SLOT(serverfail(QString)));
    connect(&l,SIGNAL(sendlog(QString)),lg,SLOT(write(QString)));
    connect(&l,SIGNAL(sendprotobuf(tutorial::SimulatorTradeReply)),lg,SLOT(writeprotobuf(tutorial::SimulatorTradeReply)));

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
