#ifndef LOG_H
#define LOG_H
#include <QThread>
#include <sys/time.h>
#include "SimulatorTradeProtos.pb.h"

class outlog : public QThread
{
    Q_OBJECT
public:
    explicit outlog(QObject *parent = 0);
    ~outlog();
protected:
    void run();
private:
    FILE *fout = fopen("/root/program/orderBetalog.txt","a");
private slots:
    void write(QString);
    void writeprotobuf(tutorial::SimulatorTradeReply);
};

#endif // LOG_H
