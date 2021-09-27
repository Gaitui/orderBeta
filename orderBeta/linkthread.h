#ifndef LINKTHREAD_H
#define LINKTHREAD_H
#include <QThread>
#include <QTcpSocket>
#include "mainwindow.h"
#include "outlog.h"
#include "SimulatorTradeProtos.pb.h"
#include <QEventLoop>
#include "google/protobuf/text_format.h"
#include <QHostAddress>
#include <fstream>
#include <sys/time.h>
#include <ostream>
//#include "link.h"

/*class linkthread : public QThread
{
    Q_OBJECT
public:
    explicit linkthread(MainWindow*,outlog*);
    ~linkthread();
protected:
    void run();
private slots:
    void receiveEnd();
};*/



class linkthread : public QThread
{
    Q_OBJECT
public:
    explicit linkthread(MainWindow*,outlog*);
    ~linkthread();
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
    //void linktoserver();
signals:
    void sendError(QString str);
    void relogin();
    void fromtcp(tutorial::SimulatorTradeReply);
    void serverfail(QString);
    void sendlog(QString);
    void sendprotobuf(tutorial::SimulatorTradeReply);
};

#endif // LINKTHREAD_H
