#ifndef UDPCONNECT_H
#define UDPCONNECT_H
#include <QHostAddress>
#include <QUdpSocket>
#include "mainwindow.h"
#include "head.h"
#include "data.h"
#include "QThread"

class udpconnect : public QUdpSocket
{
    Q_OBJECT
public:
    //udpconnect(MainWindow*,QHostAddress,int);
    udpconnect(QHostAddress,int);
    ~udpconnect();
    QHostAddress groupAddress;
    int port;
private slots:
    void readReady();
    //void receiveEnd();
signals:
    void sendUDP(QString);
    void sendnewtrack(Data);
    void sendend();
};

#endif // UDPCONNECT_H
