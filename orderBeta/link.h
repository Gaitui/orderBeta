#ifndef LINK_H
#define LINK_H
#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QByteArray>
#include <fstream>
#include "SimulatorTradeProtos.pb.h"

class link : public QTcpSocket
{
    Q_OBJECT
public:
    explicit link();
    ~link();
    bool f=true;
private:
    QTcpSocket socket;
private slots:
    void login();
    void writetohost(QString str);
    void datatohost();
    void readyRead();
signals:
    void sendError(QString str);
    void relogin();
    void fromtcp();
    void serverfail(QString);
    void sendlog(QString);
    void sendprotobuf(tutorial::SimulatorTradeReply);
};

#endif // LINK_H
