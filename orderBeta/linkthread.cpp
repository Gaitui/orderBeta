#include "linkthread.h"
//#include "link.h"

extern bool havelogin;
extern std::string logindata;
extern bool shutdown;

linkthread::linkthread(MainWindow *w, outlog *lg,Timer *t) : QThread(),con(false)
{
    connect(w,SIGNAL(sendEnd()),this,SLOT(receiveEnd()));
    connect(w,SIGNAL(sendlink(QString)),this,SLOT(writetohost(QString)));
    connect(w,SIGNAL(senddata(tutorial::SimulatorTradeOrder)),this,SLOT(datatohost(tutorial::SimulatorTradeOrder)));
    connect(this,SIGNAL(sendError(QString)),w,SLOT(showError(QString)));
    connect(this,SIGNAL(relogin()),w,SLOT(relogin()));
    connect(this,SIGNAL(fromtcp(tutorial::SimulatorTradeReply)),w,SLOT(fromtcp(tutorial::SimulatorTradeReply)));
    connect(this,SIGNAL(serverfail(QString)),w,SLOT(serverfail(QString)));
    connect(this,SIGNAL(sendlog(QString)),lg,SLOT(write(QString)));
    connect(this,SIGNAL(sendprotobuf(tutorial::SimulatorTradeReply)),lg,SLOT(writeprotobuf(tutorial::SimulatorTradeReply)));
    connect(t,SIGNAL(sendFiveSec()),this,SLOT(checkconnect()));
}
linkthread::~linkthread()
{
    if(socket->state()==QTcpSocket::ConnectedState)
        socket->disconnect();
    socket->deleteLater();
    //qDebug()<<socket->state();
    this->wait();
    this->quit();
}
void linkthread::run()
{
    inisocket();
    exec();
}
void linkthread :: inisocket()
{
    int timeout = 5000;
    socket = new QTcpSocket;
    socket->connectToHost(QHostAddress("192.168.1.124"),8004);
    if(socket->waitForConnected(timeout))
    {
         qDebug("Connect!");
         con=true;
         login();
         connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    }
    else
    {
         emit sendlog(socket->errorString());
         emit serverfail(socket->errorString());
    }
}
void linkthread :: checkconnect()
{
    if(socket->state()!=QTcpSocket::ConnectedState)
    {
        inisocket();
    }
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
    socket->waitForBytesWritten();
}

void linkthread::datatohost(tutorial::SimulatorTradeOrder order)
{
    QByteArray k(order.SerializeAsString().c_str(),order.ByteSize());
    int ssize = order.ByteSize();
    QByteArray w;
    w.append(0x7e);
    for(int i=0;i<4;i++)
    {
        w.append(ssize & 0xff);
        ssize>>=8;
    }

    socket->write(w+k);
    socket->waitForBytesWritten();
    /*
    std::string str = order.SerializeAsString();
    qDebug()<<"Origin str : "<<QString::fromStdString(str);
    int ssize = str.size();
    for(int i=0;i<str.size();i++)
    {
        w.append(str[i]);
    }
    qDebug()<<"w = "<<w.toHex();
    socket->write(w);
    socket->waitForBytesWritten();
    */

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
