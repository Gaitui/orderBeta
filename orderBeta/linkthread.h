#ifndef LINKTHREAD_H
#define LINKTHREAD_H
#include <QThread>
#include "link.h"
#include "mainwindow.h"

class linkthread : public QThread
{
    Q_OBJECT
public:
    explicit linkthread(MainWindow *w,QObject *parent = 0);
    ~linkthread();
    link l;
protected:
    void run();
};

#endif // LINKTHREAD_H
