#include "mainwindow.h"
#include "showui.h"
#include "showthread.h"
#include "linkthread.h"
#include <QApplication>
#include <QThread>
#include <queue>
#include "SimulatorTradeProtos.pb.h"
#include "outlog.h"
#include "udpthread.h"
#include <QHostAddress>


bool havelogin = false;
std::queue<int> q;
std::string logindata;
tutorial::SimulatorTradeReply reply;
tutorial::SimulatorTradeOrder order;

int main(int argc, char *argv[])
{
    qDebug()<<"main Current thread ID : "<<QThread::currentThreadId();
    FILE *fout = fopen("/root/program/orderBetalog.txt","w");
    fclose(fout);
    QApplication a(argc, argv);
    MainWindow w;
    outlog lg;
    udpthread mtse(QHostAddress("226.0.100.100"),10000);
    w.show();
    showthread rr(&w);
    linkthread ll(&w,&lg);
    lg.start();
    mtse.start();
    rr.start();
    ll.start();
    return a.exec();
}
