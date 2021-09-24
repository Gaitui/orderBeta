#ifndef UDPCONNECT_H
#define UDPCONNECT_H
#include <QUdpSocket>

class udpconnect: public QUdpSocket
{
    Q_OBJECT
public:
    explicit udpconnect(QHostAddress,int);
    ~udpconnect();
private:
    QUdpSocket *usocket;
private slots:
    void readyRead();
signals:
    void sendUDP(QString);
};

#endif // UDPCONNECT_H
