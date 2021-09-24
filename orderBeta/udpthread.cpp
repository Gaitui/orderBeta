#include "udpthread.h"

udpthread :: udpthread(QHostAddress groupAddress,int port,QObject *parent):u(groupAddress,port),QThread(parent)
{

}

udpthread :: ~udpthread()
{
    this->quit();
    this->wait();
}

void udpthread :: run()
{
    exec();
}
