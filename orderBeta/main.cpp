#include "mainwindow.h"
#include "showui.h"
#include "showthread.h"
#include "linkthread.h"
#include <QApplication>
#include <QThread>
#include <queue>
#include "outlog.h"
#include "udpthread.h"
#include <QHostAddress>


bool havelogin = false;
std::queue<int> q;
std::string logindata;
bool shutdown = false;

int main(int argc, char *argv[])
{
    qDebug()<<"main thread ID : "<<QThread::currentThreadId();
    FILE *fout = fopen("/root/program/orderBetalog.txt","w");
    fclose(fout);
    QApplication a(argc, argv);
    MainWindow w;
    outlog ol;
    udpthread mtse(&w,QHostAddress("226.0.100.100"),10000);
    linkthread lt(&w,&ol);

    ol.start();
    mtse.start();
    lt.start();
    w.show();
    return a.exec();
}
