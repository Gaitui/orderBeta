#include "link.h"

extern bool havelogin;
extern std::string logindata;
extern bool shutdown;

Link::Link():con(false)
{
    qDebug()<<"link thread ID : "<<QThread::currentThreadId();
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
        qDebug()<<"Link shutdown";
        exit(0);
    }

    login();
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    //exec();
}
Link::~Link()
{
    socket->disconnect();
}
void Link :: login(void)
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

void Link::writetohost(QString str)
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

void Link::datatohost(tutorial::SimulatorTradeOrder order)
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
    socket->waitForBytesWritten();
    //socket->flush();
}
void Link::readyRead()
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
                    qDebug()<<"login success!";
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
void Link::receiveEnd()
{
    exit(0);
}
