#include "udpthread.h"

extern bool shutdown;

udpthread :: udpthread(MainWindow *w,QHostAddress groupAddress,int port):w(w),groupAddress(groupAddress),port(port),QThread(){
}

udpthread :: ~udpthread()
{
    this->wait();
    this->quit();
}

void udpthread :: run()
{
    udpconnect newudp(groupAddress,port);
    connect(w,SIGNAL(udpEnd()),this,SLOT(receiveEnd()));
    //connect(&newudp,SIGNAL(sendend()),this,SLOT(receiveEnd()));
    connect(&newudp,SIGNAL(sendnewtrack(Data)),w,SLOT(getnewtrack(Data)));
    //newudp.moveToThread(this);
    //this->start();
    exec();
}
void udpthread::receiveEnd()
{
    exit(0);
}
