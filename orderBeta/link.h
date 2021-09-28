#ifndef LINK_H
#define LINK_H

#include <QThread>
#include <QTcpSocket>
#include "mainwindow.h"
#include "SimulatorTradeProtos.pb.h"
#include <QEventLoop>
#include "google/protobuf/text_format.h"
#include <QHostAddress>
#include <fstream>
#include <sys/time.h>

class Link : public QTcpSocket
{
    Q_OBJECT
public:
    explicit Link();
    ~Link();
    QTcpSocket *socket;
    bool con;
protected:
    void run();
private slots:
    void login();
    void writetohost(QString str);
    void datatohost(tutorial::SimulatorTradeOrder);
    void readyRead();
    void receiveEnd();
public slots:

signals:
    void sendError(QString str);
    void relogin();
    void fromtcp(tutorial::SimulatorTradeReply);
    void serverfail(QString);
    void sendlog(QString);
    void sendprotobuf(tutorial::SimulatorTradeReply);
};

#endif // LINK_H
