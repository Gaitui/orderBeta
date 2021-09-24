#include "link.h"
#include "SimulatorTradeProtos.pb.h"
#include "google/protobuf/text_format.h"
#include <QString>
#include <sstream>
#include <unistd.h>

extern tutorial::SimulatorTradeOrder order;
extern tutorial::SimulatorTradeReply reply;
extern bool havelogin;
extern std::string logindata;

link::link()
{
    int timeout = 5000;
    while(f)
    {
        socket.connectToHost(QHostAddress("192.168.1.124"),8004);
        if(!socket.waitForConnected(timeout))
        {
            emit sendlog(socket.errorString());
            emit serverfail(socket.errorString());
            sleep(5);
            continue;
        }
        f=false;
    }
    login();
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
    fin.open(root);
    if(!fin)
    {
        emit sendError(QString::fromStdString(root)+" doesn't exist");
        return;
    }
    else
    {
        fin>>logindata;
        qDebug()<<QString::fromStdString(logindata);
        writetohost(QString::fromStdString(logindata));
    }
    fin.close();
    return;
}
void link::writetohost(QString str)
{
    QByteArray w;
    int ssize = str.size();
    w.append(0x7e);
    for(int i=0;i<4;i++)
    {
        w.append(ssize & 0xff);
        ssize>>=8;
    }
    w+=str.toUtf8();
    //qDebug()<<w.toHex();
    socket.write(w);
}
void link::datatohost()
{
    std::string str = order.SerializeAsString();
    int ssize = str.size();
    QByteArray w;
    w.append(0x7e);
    for(int i=0;i<4;i++)
    {
        w.append(ssize & 0xff);
        ssize>>=8;
    }
    for(int i=0;i<str.size();i++)
        w.append(str[i]);
    //qDebug()<<w.toHex();
    socket.write(w);
}
void link::readyRead()
{
    //qDebug()<<"Ready read";
    QByteArray datas = socket.readAll();
    //qDebug()<<datas.toHex();
    for(int i=0;i<datas.size();)
    {
        if(datas[i]==0x7e)
        {
            i++;
            int dlen = 0;
            for(int j=3;j>=0;j--)
            {
                dlen=(dlen<<8)+datas[i+j];
            }
            i+=4;
            std::string dstr;
            for(int j=0;j<dlen;j++)
            {
                dstr+=datas[i+j];
            }
            if(!havelogin)
            {
                if(dstr.compare(logindata)==0)
                {
                    havelogin=true;
                    emit sendlog(QString::fromStdString(dstr)+" login success!");
                    emit relogin();
                }
                else
                {
                    emit sendlog(QString::fromStdString(dstr));
                    emit sendError("Login fail!");
                }
            }
            else
            {
                reply.ParseFromString(dstr);
                emit fromtcp();
                emit sendprotobuf(reply);
            }
            //qDebug()<<dlen;
            i+=dlen;
        }
        else
        {
            i++;
        }
    }
}
