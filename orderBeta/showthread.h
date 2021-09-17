#ifndef SHOWTHREAD_H
#define SHOWTHREAD_H
#include <QThread>
#include "showui.h"
#include "mainwindow.h"

class showthread : public QThread
{
    Q_OBJECT
public:
    explicit showthread(MainWindow *w,QObject *parent = 0);
    ~showthread();
    showui s;
protected:
    void run();
signals:

public slots:

private:
};

#endif // SHOWTHREAD_H
