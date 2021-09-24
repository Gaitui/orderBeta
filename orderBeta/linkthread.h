#ifndef LINKTHREAD_H
#define LINKTHREAD_H
#include <QThread>
#include "link.h"
#include "mainwindow.h"
#include "log.h"
#include "SimulatorTradeProtos.pb.h"

class linkthread : public QThread
{
    Q_OBJECT
public:
    explicit linkthread(MainWindow *w,outlog *lg,QObject *parent = 0);
    ~linkthread();
    link l;
protected:
    void run();
};

#endif // LINKTHREAD_H
