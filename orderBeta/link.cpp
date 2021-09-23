#include "link.h"
#include "SimulatorTradeProtos.pb.h"
#include "google/protobuf/text_format.h"
#include <QString>
#include <sstream>

extern tutorial::SimulatorTradeOrder order;
extern tutorial::SimulatorTradeReply reply;
extern bool havelogin;
extern std::string logindata;

link::link()
{
    int timeout = 5000;
    socket.connectToHost(QHostAddress("192.168.1.124"),8004);
    if(!socket.waitForConnected(timeout))
    {
        emit serverfail(socket.errorString());
        return;
    }
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
    if(f)
    {
        int timeout = 5000;
        socket.connectToHost(QHostAddress("192.168.1.124"),8004);
        if(!socket.waitForConnected(timeout))
        {
            emit serverfail(socket.errorString());
            return;
        }
        f=false;
        connect(&socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
        emit sendError("Server not ready!");
        return;
    }
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
    qDebug()<<w.toHex();
    socket.write(w);
}
void link::readyRead()
{
    qDebug()<<"Ready read";
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
                    emit relogin();
                }
                else
                {
                    emit sendError("Login fail!");
                }
            }
            else
            {
                reply.ParseFromString(dstr);
                emit fromtcp();
                /*qDebug()<<"Transct Time : "<<QString::fromStdString(reply.transacttime());
                qDebug()<<"Side : "<<QString::fromStdString(tutorial::SideEnum_Name(reply.side()));
                qDebug()<<"Symbol : "<<QString::fromStdString(reply.symbol());
                qDebug()<<"OrderQty : "<<reply.orderqty();
                qDebug()<<"Price : "<<reply.price();
                qDebug()<<"Order Type : "<<QString::fromStdString(tutorial::OrderTypeEnum_Name(reply.ordertype()));
                qDebug()<<"TSEOrder Type : "<<QString::fromStdString(reply.tseordertype());
                qDebug()<<"Time in force : "<<QString::fromStdString(tutorial::TimeInForceEnum_Name(reply.timeinforce()));
                qDebug()<<"Order ID : "<<QString::fromStdString(reply.orderid());
                qDebug()<<"NID : "<<reply.nid();
                qDebug()<<"LeavesQty : "<<reply.leavesqty();
                qDebug()<<"Order Status : "<<QString::fromStdString(tutorial::OrderStatusEnum_Name(reply.orderstatus()));
                qDebug()<<"Status Code : "<<QString::fromStdString(reply.statuscode());
                qDebug()<<"Text : "<<QString::fromStdString(reply.text());
                qDebug()<<"Reportseq : "<<reply.reportseq();
                qDebug()<<"Market : "<<QString::fromStdString(tutorial::MarketEnum_Name(reply.market()));
                qDebug()<<"";*/
                FILE *fout = fopen("/root/program/orderBetalog.txt","a");
                fprintf(fout,"%s ",reply.transacttime().c_str());
                fprintf(fout,"%s ",tutorial::SideEnum_Name(reply.side()).c_str());
                fprintf(fout,"%s ",reply.symbol().c_str());
                fprintf(fout,"%d ",reply.orderqty());
                fprintf(fout,"%.4f ",reply.price());
                fprintf(fout,"%s ",tutorial::OrderTypeEnum_Name(reply.ordertype()).c_str());
                fprintf(fout,"%s ",reply.tseordertype().c_str());
                fprintf(fout,"%s ",tutorial::TimeInForceEnum_Name(reply.timeinforce()).c_str());
                fprintf(fout,"%s ",reply.orderid().c_str());
                fprintf(fout,"%ld ",reply.nid());
                fprintf(fout,"%d ",reply.leavesqty());
                fprintf(fout,"%s ",tutorial::OrderStatusEnum_Name(reply.orderstatus()).c_str());
                fprintf(fout,"%s ",reply.statuscode().c_str());
                fprintf(fout,"%s ",reply.text().c_str());
                fprintf(fout,"%d ",reply.reportseq());
                fprintf(fout,"%s\n",tutorial::MarketEnum_Name(reply.market()).c_str());
                fclose(fout);
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
