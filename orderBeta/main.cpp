#include "mainwindow.h"
#include "showui.h"
#include "showthread.h"
#include "linkthread.h"
#include <QApplication>
#include <QThread>
#include <queue>
#include "udpthread.h"
#include <QHostAddress>
#include "udpconnect.h"
#include "data.h"
#include "format06.h"
#include "timer.h"


bool havelogin = false;
std::queue<int> q;
std::string logindata;
bool shutdown = false;

void MessageHandler(QtMsgType type,const QMessageLogContext &context,const QString &msg)
{
    static QMutex mutex;
    mutex.lock();

    QString text;
    switch(type)
    {
    case QtDebugMsg:                //qDebug()      除錯
        text = QString("Debug:");
        break;
    case QtInfoMsg:                 //qInfo()       訊息
        text = QString("Info:");
        break;
    case QtWarningMsg:              //qWarning()    警告訊息&可恢復錯誤
        text = QString("Warning:");
        break;
    case QtCriticalMsg:             //qCritical()   關鍵錯誤&系統錯誤
        text = QString("Critical:");
        break;
    case QtFatalMsg:                //qFatal()      致命錯誤
        text = QString("Fatal:");
    default:
        break;
    }

    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString message = QString::fromLocal8Bit("【%1】%2 %3 %4").arg(currentTime).arg(text).arg(msg).arg(context_info);

    QString path = QCoreApplication::applicationDirPath();
    QFile file(path + "/log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream textStream(&file);
    textStream << message << "\r\n";
    file.flush();
    file.close();

    mutex.unlock();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    qInstallMessageHandler(MessageHandler);

    qRegisterMetaType<Data>("Data");
    qRegisterMetaType<Data>("Data&");
    qDebug()<<"main thread ID : "<<QThread::currentThreadId();
    /*FILE *fout = fopen("/root/program/orderBetalog.txt","w");
    fclose(fout);*/
    MainWindow w;
    Timer t(&w);
    udpthread mtse(&w,QHostAddress("226.0.100.100"),10000);
    udpthread motc(&w,QHostAddress("226.0.30.30"),3000);
    udpthread mtseodd(&w,QHostAddress("226.8.100.100"),10008);
    udpthread motcodd(&w,QHostAddress("226.8.30.30"),3008);
    linkthread lt(&w,&t);

    t.start();
    mtse.start();
    motc.start();
    mtseodd.start();
    motcodd.start();
    lt.start();
    w.show();
    return a.exec();
}
