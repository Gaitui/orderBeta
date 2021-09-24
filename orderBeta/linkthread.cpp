#include "linkthread.h"


extern bool havelogin;
extern std::string logindata;

linkthread::linkthread(MainWindow *w, outlog *lg) : QThread(),con(false)
{
    //connect(w,SIGNAL(sendlogin()),this,SLOT(login()));
    //connect(w,SIGNAL(linktoserver()),this,SLOT(load()));
    connect(w,SIGNAL(sendlink(QString)),this,SLOT(writetohost(QString)));
    connect(w,SIGNAL(senddata()),this,SLOT(datatohost()));
    connect(this,SIGNAL(sendError(QString)),w,SLOT(showError(QString)));
    connect(this,SIGNAL(relogin()),w,SLOT(relogin()));
    connect(this,SIGNAL(fromtcp()),w,SLOT(fromtcp()));
    connect(this,SIGNAL(serverfail(QString)),w,SLOT(serverfail(QString)));
    connect(this,SIGNAL(sendlog(QString)),lg,SLOT(write(QString)));
    connect(this,SIGNAL(sendprotobuf(tutorial::SimulatorTradeReply)),lg,SLOT(writeprotobuf(tutorial::SimulatorTradeReply)));
}
linkthread::~linkthread()
{
    socket->close();
    this->wait();
    this->quit();
}
void linkthread::run()
{
    qDebug()<<"linkthread Current thread ID : "<<QThread::currentThreadId();
    socket = new QTcpSocket;
    int timeout = 5000;
    while(!con)
    {
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
            sleep(5);
        }
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
    }
    fin.close();
    return;
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
    socket->flush();
}

void linkthread::datatohost(tutorial::SimulatorTradeOrder order)
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
    socket->write(w);
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
                emit fromtcp();
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
