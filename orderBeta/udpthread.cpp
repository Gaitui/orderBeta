#include "udpthread.h"

extern bool shutdown;

udpthread :: udpthread(MainWindow *w,QHostAddress groupAddress,int port):groupAddress(groupAddress),port(port),QThread()
{
    //connect(w,SIGNAL(udpEnd()),this,SLOT(receiveEnd()));
}

udpthread :: ~udpthread()
{
    qDebug()<<"udpthread shut down";
    this->wait();
    this->quit();
}

void udpthread :: run()
{
    qDebug()<<groupAddress;
    qDebug()<<port;
    usocket = new QUdpSocket;
    usocket->bind(QHostAddress::AnyIPv4,port,QUdpSocket::ShareAddress);
    usocket->joinMulticastGroup(groupAddress);
    connect(usocket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    exec();
}
void udpthread::readyRead()
{
    QHostAddress sender;
    quint16 senderport;
    while(usocket->hasPendingDatagrams())
    {
        QByteArray datagram;

        datagram.resize(usocket->pendingDatagramSize());
        usocket->readDatagram(datagram.data(),datagram.size(),&sender,&senderport);
        qDebug()<<"Message From "<<sender.toString();
        qDebug()<<"Port From "<<senderport;
        qDebug()<<"Message :: "<<datagram.toHex();
        std::string str = datagram.toStdString();
        printf("%02x\n",str[0]);
    }
    exec();
}
void udpthread::receiveEnd()
{
    usocket->close();
}
