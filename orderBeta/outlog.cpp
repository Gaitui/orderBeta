#include "outlog.h"

outlog::outlog(QObject *parent): QThread(parent){}

void outlog::run()
{
    exec();
}
outlog::~outlog()
{
    fclose(fout);
    this->quit();
    this->wait();
}

void outlog::write(QString str)
{
    timeval curtime;
    gettimeofday(&curtime,NULL);
    int milisec = curtime.tv_usec/1000;
    tm *local = localtime(&curtime.tv_sec);
    fprintf(fout,"[%02d:%02d:%02d.%03d] %s\n",local->tm_hour,local->tm_min,local->tm_sec,milisec,str.toStdString().c_str());
    fflush(fout);
}
void outlog::writeprotobuf(tutorial::SimulatorTradeReply reply)
{
    timeval curtime;
    gettimeofday(&curtime,NULL);
    int milisec = curtime.tv_usec/1000;
    tm *local = localtime(&curtime.tv_sec);
    fprintf(fout,"[%02d:%02d:%02d.%03d] ",local->tm_hour,local->tm_min,local->tm_sec,milisec);
    fprintf(fout,"%s ",reply.transacttime().c_str());
    fprintf(fout,"%s ",tutorial::SideEnum_Name(reply.side()).c_str());
    fprintf(fout,"%s ",reply.symbol().c_str());
    fprintf(fout,"%d ",reply.orderqty());
    fprintf(fout,"%.4f ",reply.price());
    fprintf(fout,"%s ",tutorial::OrderTypeEnum_Name(reply.ordertype()).c_str());
    fprintf(fout,"%s ",reply.tseordertype().c_str());
    fprintf(fout,"%s ",tutorial::TimeInForceEnum_Name(reply.timeinforce()).c_str());
    fprintf(fout,"%s ",reply.orderid().c_str());
    fprintf(fout,"%ld ",reply.nid());
    fprintf(fout,"%d ",reply.leavesqty());
    fprintf(fout,"%s ",tutorial::OrderStatusEnum_Name(reply.orderstatus()).c_str());
    fprintf(fout,"%s ",reply.statuscode().c_str());
    fprintf(fout,"%s ",reply.text().c_str());
    fprintf(fout,"%d ",reply.reportseq());
    fprintf(fout,"%s\n",tutorial::MarketEnum_Name(reply.market()).c_str());
    fflush(fout);
}
