#include "link.h"
#include <QHostAddress>
#include <QByteArray>
#include <QByteArray>

link::link()
{
    socket.connectToHost(QHostAddress("192.168.1.124"),8004);
    f=false;
    connect(&socket,SIGNAL(readyRead()),this,SLOT(fromHost()));
}
link::~link()
{
    socket.disconnect();
}
void link::writetohost(QString str)
{
    while(f);
    QByteArray w;
    w.append(0x7e);
    w.append(str.size());
    w.append((char) 0x00);
    w.append((char) 0x00);
    if(str.size()%2!=0)
        w.append((char) 0x00);
    w+=str.toUtf8();
    qDebug()<<w;
    socket.write(w);
}

/*void link::fromhost()
{
    qDebug()<<"Ready read";
    QByteArray datas = socket.readAll();
    qDebug()<<datas;
}*/
