#include "timer.h"

Timer::Timer(MainWindow* w):Run(true)
{
    connect(w,SIGNAL(sendEnd()),this,SLOT(Stop()));
}
Timer::~Timer()
{
    this->wait();
    this->quit();
}

void Timer::run()
{
    time_t lsec,nsec;
    nsec=time(NULL);
    lsec=nsec;
    while(Run)
    {
        nsec=time(NULL);
        if(difftime(nsec,lsec) >=5)
        {
            lsec = nsec;
            emit sendFiveSec();
        }
    }
    exit(0);
}
void Timer::Stop()
{
    Run = false;
}
