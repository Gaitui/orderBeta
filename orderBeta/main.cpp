#include "mainwindow.h"
#include "showui.h"
#include "showthread.h"
#include "linkthread.h"
#include <QApplication>
#include <QThread>
#include <queue>
#include "SimulatorTradeProtos.pb.h"


bool havelogin = false;
std::queue<int> q;
std::string logindata;
tutorial::SimulatorTradeReply reply;
tutorial::SimulatorTradeOrder order;

int main(int argc, char *argv[])
{
    FILE *fout = fopen("/root/program/orderBetalog.txt","w");
    fclose(fout);
    QApplication a(argc, argv);
    MainWindow w;
    showthread rr(&w);
    linkthread ll(&w);
    w.show();
    rr.start();
    ll.start();
    return a.exec();
}
