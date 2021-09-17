#include "showthread.h"
#include <unistd.h>

showthread::showthread(MainWindow *w, QObject *parent) : QThread(parent)
{
    s.moveToThread(this);
    connect(&s,SIGNAL(sendshow(int)),w,SLOT(getshow(int)));
}

showthread::~showthread()
{
    this->quit();
    this->wait();
}

void showthread::run()
{

    for(int i=0;i<5;i++)
    {
        sleep(1);
        s.runui(i);
    }
    exec();
}

