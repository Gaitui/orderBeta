#include "udpconnect.h"

udpconnect::udpconnect(QHostAddress groupAddress,int port)
{
    //qDebug()<<"RRR";
    qDebug()<<groupAddress;
    qDebug()<<port;
    usocket = new QUdpSocket(this);
    usocket->bind(QHostAddress::AnyIPv4,port,QUdpSocket::ShareAddress);
    usocket->joinMulticastGroup(groupAddress);
    connect(usocket,SIGNAL(readyRead()),this,SLOT(readyRead()));
}
udpconnect::~udpconnect()
{
    usocket->close();
}
void udpconnect::readyRead()
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
}
