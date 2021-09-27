#include "linkthread.h"
//#include "link.h"

extern bool havelogin;
extern std::string logindata;
extern bool shutdown;

linkthread::linkthread(MainWindow *w, outlog *lg) : QThread(),con(false)
{
    //connect(w,SIGNAL(sendlogin()),this,SLOT(login()));
    connect(w,SIGNAL(sendEnd()),this,SLOT(receiveEnd()));
    connect(w,SIGNAL(sendlink(QString)),this,SLOT(writetohost(QString)));
    connect(w,SIGNAL(senddata(tutorial::SimulatorTradeOrder)),this,SLOT(datatohost(tutorial::SimulatorTradeOrder)));
    connect(this,SIGNAL(sendError(QString)),w,SLOT(showError(QString)));
    connect(this,SIGNAL(relogin()),w,SLOT(relogin()));
    connect(this,SIGNAL(fromtcp(tutorial::SimulatorTradeReply)),w,SLOT(fromtcp(tutorial::SimulatorTradeReply)));
    connect(this,SIGNAL(serverfail(QString)),w,SLOT(serverfail(QString)));
    connect(this,SIGNAL(sendlog(QString)),lg,SLOT(write(QString)));
    connect(this,SIGNAL(sendprotobuf(tutorial::SimulatorTradeReply)),lg,SLOT(writeprotobuf(tutorial::SimulatorTradeReply)));
}
linkthread::~linkthread()
{
    if(socket->state()==QTcpSocket::ConnectedState)
        socket->disconnect();
    socket->deleteLater();
    qDebug()<<socket->state();
    this->wait();
    this->quit();
}
void linkthread::run()
{
    qDebug()<<"linkthread thread ID : "<<QThread::currentThreadId();
    socket = new QTcpSocket;
    int timeout = 5000;
    time_t lsec,nsec;
    nsec=time(NULL);
    lsec=nsec-5;
    while(!con && !shutdown)
    {
        nsec=time(NULL);
        if(difftime(nsec,lsec) >=5)
        {
            lsec = nsec;
            socket->connectToHost(QHostAddress("192.168.1.124"),8004);
            if(socket->waitForConnected(timeout))
            {
                qDebug("Connect!");
                con=true;
                break;
            }
            else
            {
                qDebug("Hello!");
                emit sendlog(socket->errorString());
                emit serverfail(socket->errorString());
            }
        }
    }
    if(shutdown)
    {
        //qDebug()<<"RR";
        exit(0);
    }

    login();
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    exec();
}
void linkthread :: login(void)
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
        writetohost(QString::fromStdString(logindata));
        fin.close();
    }

}

void linkthread::writetohost(QString str)
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
    socket->write(w);
    //socket->flush();
    socket->waitForBytesWritten();
}

void linkthread::datatohost(tutorial::SimulatorTradeOrder order)
{
    qDebug()<<"Ori Price"<<order.price();
    qDebug()<<"Ori Market"<<order.market();
    qDebug()<<order.ByteSize();

    QByteArray k(order.SerializeAsString().c_str(),order.ByteSize());
    qDebug()<<"k = "<<k.toHex();
    //std::string str = order.SerializeAsString();
    //qDebug()<<"Origin str : "<<QString::fromStdString(str);
    int ssize = order.ByteSize();
    QByteArray w;
    w.append(0x7e);
    for(int i=0;i<4;i++)
    {
        w.append(ssize & 0xff);
        ssize>>=8;
    }
    /*for(int i=0;i<str.size();i++)
    {
        //if(str[i]!='\)')
        w.append(str[i]);
    }
    qDebug()<<"w = "<<w.toHex();
    std::string tempstr;
    int dlen = 0;
    for(int j=3;j>=0;j--)
    {
        dlen=(dlen<<8)+w[j+1];
    }
    for(int j=0;j<dlen;j++)
    {
        tempstr+=w[5+j];
    }*/
    tutorial::SimulatorTradeOrder temp;
    temp.ParseFromArray(k.data(),k.size());

    qDebug()<<"wside : "<<QString::fromStdString(tutorial::SideEnum_Name(temp.side()));
    qDebug()<<"wsymbol : "<<QString::fromStdString(temp.symbol());
    qDebug()<<"worderqty: "<<QString::number(temp.orderqty());
    qDebug()<<"wprice : "<<QString::number(temp.price(),'f',2);
    qDebug()<<"wtype : "<<QString::fromStdString(tutorial::OrderTypeEnum_Name(temp.ordertype()));
    qDebug()<<"wTSEType : "<<QString::fromStdString(temp.tseordertype());
    qDebug()<<"wTimeInFo : "<<QString::fromStdString(tutorial::TimeInForceEnum_Name(temp.timeinforce()));
    qDebug()<<"wMarket : "<<QString::fromStdString(tutorial::MarketEnum_Name(temp.market()));


    socket->write(w+k);
    socket->waitForBytesWritten();
}
void linkthread::readyRead()
{
    qDebug()<<"Ready read";
    QByteArray datas = socket->readAll();
    tutorial::SimulatorTradeReply reply;
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
                emit fromtcp(reply);
                emit sendprotobuf(reply);
            }
            i+=dlen;
        }
        else
        {
            i++;
        }
    }
}
void linkthread::receiveEnd()
{
    exit(0);
}
