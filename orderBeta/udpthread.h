#ifndef UDPTHREAD_H
#define UDPTHREAD_H
#include <QThread>
#include <QHostAddress>
#include <QUdpSocket>
#include "mainwindow.h"
#include "head.h"
#include "data.h"
#include "udpconnect.h"


class udpthread : public QThread
{
    Q_OBJECT
public:
    explicit udpthread(MainWindow*,QHostAddress,int);
    ~udpthread();
    MainWindow *w;
    QHostAddress groupAddress;
    int port;
protected:
    void run();
private slots:
    void receiveEnd();
signals:
};


/*class udpthread : public QThread
{
    Q_OBJECT
public:
    explicit udpthread(MainWindow*,QHostAddress,int);
    ~udpthread();
    //udpconnect u;
    QUdpSocket *usocket;
    QHostAddress groupAddress;
    int port;
protected:
    void run();
private slots:
    void readyRead();
    void receiveEnd();
signals:
    void sendUDP(QString);
    void sendnewtrack(Data);
};*/

#endif // UDPTHREAD_H
