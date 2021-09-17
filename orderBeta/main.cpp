#include "mainwindow.h"
#include "showui.h"
#include "showthread.h"
#include <QApplication>
#include <QThread>
#include <queue>

bool login = false;
std::queue<int> q;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    showthread rr(&w);
    //QThread* thread = new QThread;

    //QObject::connect(s,SIGNAL(sendshow()),&w,SLOT(getshow(int &)));
    //QObject::connect(thread,&QThread::finished,s,&QThread::deleteLater);

    //w.getshow.moveToThread(thread);
    //thread->start();
    w.show();
    rr.start();
    return a.exec();
}
