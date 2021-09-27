#include "udpthread.h"

extern bool shutdown;

udpthread :: udpthread(MainWindow *w,QHostAddress groupAddress,int port):groupAddress(groupAddress),port(port),QThread()
{
    connect(w,SIGNAL(udpEnd()),this,SLOT(receiveEnd()));
    connect(this,SIGNAL(sendnewtrack(Data)),w,SLOT(getnewtrack(Data)));
}

udpthread :: ~udpthread()
{
    if(usocket->state() == QUdpSocket::ConnectedState)
        usocket->disconnect();
    usocket->deleteLater();
    //qDebug()<<"udpthread shut down";
    this->wait();
    this->quit();

}

void udpthread :: run()
{
    //qDebug()<<groupAddress;
    //qDebug()<<port;
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
        //qDebug()<<"Message From "<<sender.toString();
        //qDebug()<<"Port From "<<senderport;
        //qDebug()<<"Message :: "<<datagram.toHex();
        std::string pkt_data = datagram.toStdString();
        //printf("%02x\n",str[0]);
        int h=0;
        int len = pkt_data.size();
        while(h<len)
        {
            if(pkt_data[h]==27)
            {
                if(h+10<=len)
                {
                    head dhead;
                    dhead.decode(pkt_data,h);
                    qDebug()<<"Esc : "<<dhead.esc<<" Len : "<<dhead.mlen<<" Type : "<<dhead.mtype<<" Code : "<<dhead.mcode<<" Ver : "<<dhead.mver<<" Seq : "<<dhead.mseq;
                    if(h+dhead.mlen<=len && pkt_data[h+dhead.mlen-2]==0x0d && pkt_data[h+dhead.mlen-1]==0x0a)
                    {
                        if(dhead.mcode==6 || dhead.mcode==23)
                        {
                            qDebug()<<"AA";
                            Data newdata;
                            newdata.dhead = dhead;
                            for(int i=10;i<dhead.mlen;i++)
                            {
                                newdata.pkt_data+=pkt_data[h+i];
                            }
                            emit sendnewtrack(newdata);
                        }
                        h+=dhead.mlen-1;
                    }
                }
            }
            h++;
        }
    }
}
void udpthread::receiveEnd()
{
    exit(0);
}
