#ifndef UDPTHREAD_H
#define UDPTHREAD_H
#include <QThread>
#include <QHostAddress>
#include "udpconnect.h"

class udpthread : public QThread
{
    Q_OBJECT
public:
    explicit udpthread(QHostAddress,int,QObject *parent=0);
    ~udpthread();
    udpconnect u;
protected:
    void run();
};

#endif // UDPTHREAD_H
