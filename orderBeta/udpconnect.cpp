#include "udpconnect.h"

udpconnect::udpconnect(QHostAddress groupAddress,int port):groupAddress(groupAddress),port(port)
{
    qDebug()<<"In Udp connect!";
    bind(QHostAddress::AnyIPv4,port,QUdpSocket::ShareAddress);
    joinMulticastGroup(groupAddress);
    connect(this,SIGNAL(readyRead()),this,SLOT(readReady()));
}

void udpconnect::readReady()
{
    QHostAddress sender;
    quint16 senderport;
    while(hasPendingDatagrams())
    {
        QByteArray datagram;

        datagram.resize(pendingDatagramSize());
        readDatagram(datagram.data(),datagram.size(),&sender,&senderport);
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
                    //qDebug()<<"Esc : "<<dhead.esc<<" Len : "<<dhead.mlen<<" Type : "<<dhead.mtype<<" Code : "<<dhead.mcode<<" Ver : "<<dhead.mver<<" Seq : "<<dhead.mseq;
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
void udpconnect::receiveEnd()
{
    disconnect();
    this->deleteLater();
    exit(0);
}
