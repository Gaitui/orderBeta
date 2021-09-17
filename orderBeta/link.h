#ifndef LINK_H
#define LINK_H
#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>

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
    void writetohost(QString str);
signals:
    void fromhost();
};

#endif // LINK_H
