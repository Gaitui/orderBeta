#include "link.h"
#include "SimulatorTradeProtos.pb.h"
#include "google/protobuf/text_format.h"
#include <QString>
#include <sstream>

extern tutorial::SimulatorTradeOrder order;

link::link()
{
    socket.connectToHost(QHostAddress("192.168.1.124"),8004);
    f=false;
    connect(&socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
}
link::~link()
{
    socket.disconnect();
}
void link::login(void)
{
    std::ifstream fin;
    std::string root = "/root/program/orderBeta/orderBeta/login.ini";
    //std::string root = "login.ini";
    fin.open(root);
    if(!fin)
    {
        emit sendError(QString::fromStdString(root)+" doesn't exist");
        return;
    }
    else
    {
        std::string str;
        fin>>str;
        qDebug()<<QString::fromStdString(str);
        writetohost(QString::fromStdString(str));
    }
    fin.close();
    return;
}
void link::writetohost(QString str)
{
    while(f);
    QByteArray w;
    int ssize = str.size();
    w.append(0x7e);
    for(int i=0;i<4;i++)
    {
        w.append(ssize & 0xff);
        ssize>>=8;
    }
    w+=str.toUtf8();
    qDebug()<<w.toHex();
    socket.write(w);
}
void link::datatohost()
{
    //while(f);
    std::string str = order.SerializeAsString();
    qDebug("%s",str.c_str());
    QByteArray w;
    int ssize = str.size();
    w.append(0x7e);
    for(int i=0;i<4;i++)
    {
        qDebug()<<ssize;
        w.append(ssize & 0xff);
        ssize>>=8;
        //w.append(ssize%100);
        //ssize/=100;
    }
    std::ostringstream out;
    order.SerializeToOstream(&out);
    QByteArray k(out.str().c_str());
    qDebug()<<w.toHex()<<k.toHex();
    socket.write(w+k);
}
void link::readyRead()
{
    qDebug()<<"Ready read";
    QByteArray datas = socket.readAll();
    qDebug()<<datas;
}
