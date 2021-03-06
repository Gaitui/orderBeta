#ifndef LINKTHREAD_H
#define LINKTHREAD_H
#include <QThread>
#include <QTcpSocket>
#include "mainwindow.h"
#include "SimulatorTradeProtos.pb.h"
#include <QEventLoop>
#include "google/protobuf/text_format.h"
#include <QHostAddress>
#include <fstream>
#include <sys/time.h>
#include <ostream>
#include "timer.h"


class linkthread : public QThread
{
    Q_OBJECT
public:
    explicit linkthread(MainWindow*,Timer*);
    ~linkthread();
    QTcpSocket *socket;
    bool con;
protected:
    void run();
    void inisocket();
private slots:
    void login();
    void writetohost(QString str);
    void datatohost(tutorial::SimulatorTradeOrder);
    void readyRead();
    void receiveEnd();
    void checkconnect();
public slots:
    //void linktoserver();
signals:
    void sendError(QString str);
    void relogin();
    void fromtcp(tutorial::SimulatorTradeReply);
    void serverfail(QString);
};

#endif // LINKTHREAD_H
