#include "udpconnect.h"

udpconnect::udpconnect(QHostAddress groupAddress,int port):groupAddress(groupAddress),port(port)
{
    //qDebug()<<"In Udp connect!";
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
        u_char *pkt_data = new u_char[datagram.size()];
        std::memcpy(pkt_data,datagram.data(),datagram.size());
        //printf("%02x\n",str[0]);
        //qDebug("Pktdata : %02x %02x",pkt_data[1],pkt_data[2]);
        int h=0;
        int len = datagram.size();
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
                        if(dhead.mcode==1 || dhead.mcode==6 || dhead.mcode==23)
                        {
                            //qDebug()<<"Message :: "<<datagram.toHex();
                            Data newdata;
                            newdata.dhead = dhead;
                            newdata.pkt_data = new u_char[dhead.mlen];
                            for(int i=0;i<dhead.mlen;i++)
                            {
                                newdata.pkt_data[i]=(pkt_data[h+i] & 0xff);
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
