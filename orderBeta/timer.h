#ifndef TIMER_H
#define TIMER_H
#include <QThread>
#include "mainwindow.h"

class Timer : public QThread
{
    Q_OBJECT
public:
    Timer(MainWindow*);
    ~Timer();
    bool Run;
protected:
    void run();
signals:
    void sendFiveSec();
private slots:
    void Stop();
};

#endif // TIMER_H
