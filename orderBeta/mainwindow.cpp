#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SimulatorTradeProtos.pb.h"
#include "google/protobuf/text_format.h"
#include <sstream>
#include <QPushButton>
#include <QAbstractItemView>

extern bool havelogin;
extern std::string logindata;
extern std::queue<int> q;
extern tutorial::SimulatorTradeOrder order;
extern tutorial::SimulatorTradeReply reply;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStandardItemModel *rmodel = new QStandardItemModel(0,10,this);
    rmodel->setHorizontalHeaderItem(0,new QStandardItem(QString("時間")));
    rmodel->setHorizontalHeaderItem(1,new QStandardItem(QString("商品代號")));
    rmodel->setHorizontalHeaderItem(2,new QStandardItem(QString("市場")));
    rmodel->setHorizontalHeaderItem(3,new QStandardItem(QString("成交量")));
    rmodel->setHorizontalHeaderItem(4,new QStandardItem(QString("成交價")));
    rmodel->setHorizontalHeaderItem(5,new QStandardItem(QString("買進張數")));
    rmodel->setHorizontalHeaderItem(6,new QStandardItem(QString("買進價格")));
    rmodel->setHorizontalHeaderItem(7,new QStandardItem(QString("賣出張數")));
    rmodel->setHorizontalHeaderItem(8,new QStandardItem(QString("賣出價格")));
    rmodel->setHorizontalHeaderItem(9,new QStandardItem(QString("")));
    ui->realtime->setModel(rmodel);





    QStandardItemModel *enmodel = new QStandardItemModel(0,14,this);
    enmodel->setHorizontalHeaderItem(0,new QStandardItem(QString("時間")));
    enmodel->setHorizontalHeaderItem(1,new QStandardItem(QString("單號")));
    enmodel->setHorizontalHeaderItem(2,new QStandardItem(QString("商品代號")));
    enmodel->setHorizontalHeaderItem(3,new QStandardItem(QString("市場")));
    enmodel->setHorizontalHeaderItem(4,new QStandardItem(QString("委託條件")));
    enmodel->setHorizontalHeaderItem(5,new QStandardItem(QString("買賣")));
    enmodel->setHorizontalHeaderItem(6,new QStandardItem(QString("委託價")));
    enmodel->setHorizontalHeaderItem(7,new QStandardItem(QString("修改價格")));
    enmodel->setHorizontalHeaderItem(8,new QStandardItem(QString("委託數")));
    enmodel->setHorizontalHeaderItem(9,new QStandardItem(QString("成交數")));
    enmodel->setHorizontalHeaderItem(10,new QStandardItem(QString("剩餘數")));
    enmodel->setHorizontalHeaderItem(11,new QStandardItem(QString("修改數量")));
    enmodel->setHorizontalHeaderItem(12,new QStandardItem(QString("送出")));
    enmodel->setHorizontalHeaderItem(13,new QStandardItem(QString("刪除")));
    ui->nowentrust->setModel(enmodel);

    QStandardItemModel *dmodel = new QStandardItemModel(0,6,this);
    dmodel->setHorizontalHeaderItem(0,new QStandardItem(QString("時間")));
    dmodel->setHorizontalHeaderItem(1,new QStandardItem(QString("單號")));
    dmodel->setHorizontalHeaderItem(2,new QStandardItem(QString("商品代號")));
    dmodel->setHorizontalHeaderItem(3,new QStandardItem(QString("買賣")));
    dmodel->setHorizontalHeaderItem(4,new QStandardItem(QString("成交價")));
    dmodel->setHorizontalHeaderItem(5,new QStandardItem(QString("成交數")));

    ui->deal->setModel(dmodel);

    QStandardItemModel *hmodel = new QStandardItemModel(0,8,this);
    hmodel->setHorizontalHeaderItem(0,new QStandardItem(QString("時間")));
    hmodel->setHorizontalHeaderItem(1,new QStandardItem(QString("單號")));
    hmodel->setHorizontalHeaderItem(2,new QStandardItem(QString("商品代號")));
    hmodel->setHorizontalHeaderItem(3,new QStandardItem(QString("買賣")));
    hmodel->setHorizontalHeaderItem(4,new QStandardItem(QString("委託價")));
    hmodel->setHorizontalHeaderItem(5,new QStandardItem(QString("數量")));
    hmodel->setHorizontalHeaderItem(6,new QStandardItem(QString("狀態")));
    hmodel->setHorizontalHeaderItem(7,new QStandardItem(QString("原因")));
    ui->passentrust->setModel(hmodel);

    ui->newmarket->addItem("上市",0);
    ui->newmarket->addItem("上櫃",1);

    ui->newortype->addItem("市價",0);
    ui->newortype->addItem("限價",1);

    ui->newentype->addItem("整股",0);
    ui->newentype->addItem("零股",1);

    ui->newrequest->addItem("ROD",0);
    ui->newrequest->addItem("IOC",1);
    ui->newrequest->addItem("FOK",2);

    ui->newbuysell->addItem("買",0);
    ui->newbuysell->addItem("賣",1);

    QRegExp doublerx("[0-9]{0,6}[\.][0-9]{0,4}");
    ui->newenprice->setValidator(new QRegExpValidator(doublerx,this));

    ui->newennum->setValidator(new QIntValidator(1,1e9,this));

    if(havelogin)
    {
        ui->login->setEnabled(false);
    }
    else
    {
        ui->login->setEnabled(true);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exit_clicked()
{
    close();
}

void MainWindow::getshow(int k)
{
    int rownum;
    QStandardItemModel *rmodel = (QStandardItemModel *)ui->realtime->model();

    rownum = rmodel->rowCount();
    QStandardItem *i0 = new QStandardItem("Time"+QString::number(k));
    QStandardItem *i1 = new QStandardItem(QString::number(k));
    QStandardItem *i2 = new QStandardItem("Market");
    QStandardItem *i3 = new QStandardItem("Deal Num "+QString::number(k));
    QStandardItem *i4 = new QStandardItem("Deal Price "+QString::number(k));
    QStandardItem *i5 = new QStandardItem("Buy Num "+QString::number(k));
    QStandardItem *i6 = new QStandardItem("Buy price "+QString::number(k));
    QStandardItem *i7 = new QStandardItem("Sell price "+QString::number(k));
    QStandardItem *i8 = new QStandardItem("Sell Num "+QString::number(k));


    rmodel->QStandardItemModel::setItem(rownum,0,i0);
    rmodel->QStandardItemModel::setItem(rownum,1,i1);
    rmodel->QStandardItemModel::setItem(rownum,2,i2);
    rmodel->QStandardItemModel::setItem(rownum,3,i3);
    rmodel->QStandardItemModel::setItem(rownum,4,i4);
    rmodel->QStandardItemModel::setItem(rownum,5,i5);
    rmodel->QStandardItemModel::setItem(rownum,6,i6);
    rmodel->QStandardItemModel::setItem(rownum,7,i7);
    rmodel->QStandardItemModel::setItem(rownum,8,i8);

    QPushButton *btn = new QPushButton("Delete");
    btn->setProperty("id",rmodel->rowCount());
    btn->setProperty("action","delete");
    ui->realtime->setIndexWidget(rmodel->index(rownum,9),btn);

    return;
}

void MainWindow::on_login_clicked()
{
    emit sendlogin();
}

void MainWindow::showError(QString str)
{
    QMessageBox::warning(NULL,"ERROR",str);
}

void MainWindow::relogin()
{
    QMessageBox::information(NULL,"Succss","Login Success!");
    timeval curtime;
    gettimeofday(&curtime,NULL);
    int milisec = curtime.tv_usec/1000;
    tm *local = localtime(&curtime.tv_sec);
    QString tempstr;
    tempstr.sprintf("%02d:%02d:%02d.%03d",local->tm_hour,local->tm_min,local->tm_sec,milisec);
    ui->record->append(tempstr +" "+ QString::fromStdString(logindata) + " login Success");
    ui->login->setEnabled(false);
}

void MainWindow::on_sendNew_clicked()
{
    if(!havelogin)
    {
        showError("Please login!");
        return;
    }
    if(ui->newscode->text().size()==0)
    {
        showError("Need Stock Code!");
        return;
    }
    if(ui->newenprice->text().size()==0)
    {
        showError("Need Entrust Price!");
        return;
    }
    if(ui->newennum->text().size()==0)
    {
        showError("Need Entrust Number!");
        return;
    }
    else
    {
        if(ui->newennum->text().toInt()==0)
        {
            showError("Entrust Number Must > 0 !");
            return;
        }
    }
    QMessageBox::StandardButton check = QMessageBox::information(NULL,"Send new order","Send this New Order?",QMessageBox::Yes | QMessageBox::No);
    if(check == QMessageBox::No)
        return;
    timeval curtime;
    gettimeofday(&curtime,NULL);
    int milisec = curtime.tv_usec/1000;
    tm *local = localtime(&curtime.tv_sec);
    QString tempstr;
    tempstr.sprintf("%02d%02d%02d%03d%03d",local->tm_hour,local->tm_min,local->tm_sec,milisec,0);


    order.Clear();
    //1
    order.set_transacttime(tempstr.toStdString().c_str());
    //2
    if(ui->newbuysell->currentIndex()==0)
    {
        order.set_side(tutorial::SideEnum::sBuy);
    }
    else
    {
        order.set_side(tutorial::SideEnum::sSell);
    }

    //3
    order.set_symbol(ui->newscode->text().toStdString().c_str());
    //4
    order.set_orderqty(ui->newennum->text().toInt());
    //5
    double newprice = ui->newenprice->text().toDouble();
    //qDebug()<<"New Price : "<<newprice;
    order.set_price(newprice);
    //qDebug()<<"Set Price"<<order.price();
    //6
    if(ui->newortype->currentIndex()==0)
        order.set_ordertype(tutorial::OrderTypeEnum::otMarket);
    else
        order.set_ordertype(tutorial::OrderTypeEnum::otLimit);
    //7
    //order.set_tseordertype("");
    //8
    if(ui->newrequest->currentIndex()==0)
        order.set_timeinforce(tutorial::TimeInForceEnum::tifROD);
    else if(ui->newrequest->currentIndex()==1)
        order.set_timeinforce(tutorial::TimeInForceEnum::tifIOC);
    else
        order.set_timeinforce(tutorial::TimeInForceEnum::tifFOK);
    //9
    order.set_nid(129);
    //10
    if(ui->newmarket->currentIndex()==0)
    {
        if(ui->newentype->currentIndex()==0)
            order.set_market(tutorial::MarketEnum::mTSE);
        else
            order.set_market(tutorial::MarketEnum::mTSE_ODD);
    }
    else
    {
        if(ui->newentype->currentIndex()==0)
            order.set_market(tutorial::MarketEnum::mOTC);
        else
            order.set_market(tutorial::MarketEnum::mOTC_ODD);
    }/**/
    //order.set_market(tutorial::MarketEnum::mFutures);
    //11
    order.set_orderid("0");
    //12
    order.set_kind(tutorial::KindEnum::kNew);

    emit senddata();
}

void MainWindow::fromtcp()
{
    if(reply.orderstatus()==2)
    {
        QStandardItemModel *model = (QStandardItemModel *)ui->nowentrust->model();
        int rownum = model->rowCount();
        QStandardItem *i0 = new QStandardItem(QString::fromStdString(reply.transacttime()));
        QStandardItem *i1 = new QStandardItem(QString::fromStdString(reply.orderid()));
        QStandardItem *i2 = new QStandardItem(QString::fromStdString(reply.symbol()));
        QStandardItem *i3 = new QStandardItem(QString::fromStdString(tutorial::MarketEnum_Name(reply.market())));
        QStandardItem *i4 = new QStandardItem(QString::fromStdString(tutorial::TimeInForceEnum_Name(reply.timeinforce())));
        QStandardItem *i5 = new QStandardItem(QString::fromStdString(tutorial::SideEnum_Name(reply.side())));
        QStandardItem *i6 = new QStandardItem(QString::number(reply.price()));

        QStandardItem *i8 = new QStandardItem(QString::number(reply.orderqty()));
        QStandardItem *i9 = new QStandardItem(QString::number(0));
        QStandardItem *i10 = new QStandardItem(QString::number(reply.orderqty()));



        model->QStandardItemModel::setItem(rownum,0,i0);
        model->QStandardItemModel::setItem(rownum,1,i1);
        model->QStandardItemModel::setItem(rownum,2,i2);
        model->QStandardItemModel::setItem(rownum,3,i3);
        model->QStandardItemModel::setItem(rownum,4,i4);
        model->QStandardItemModel::setItem(rownum,5,i5);
        model->QStandardItemModel::setItem(rownum,6,i6);

        model->QStandardItemModel::setItem(rownum,8,i8);
        model->QStandardItemModel::setItem(rownum,9,i9);
        model->QStandardItemModel::setItem(rownum,10,i10);

        QPushButton *bm = new QPushButton("Send");
        bm->setProperty("id",model->rowCount());
        bm->setProperty("action","modify");
        ui->nowentrust->setIndexWidget(model->index(rownum,12),bm);

        QPushButton *bd = new QPushButton("Delete");
        bd->setProperty("id",model->rowCount());
        bd->setProperty("action","Delete");
        ui->nowentrust->setIndexWidget(model->index(rownum,13),bd);

        connect(bd,SIGNAL(clicked()),this,SLOT(delbuttonclick()));
    }
    else if(reply.orderstatus()==7)
    {
        QStandardItemModel *nmodel = (QStandardItemModel *)ui->nowentrust->model();
        int rownum;
        for(rownum=0;rownum<nmodel->rowCount();rownum++)
        {
            if(reply.orderid().compare(nmodel->index(rownum,1).data().toString().toStdString())==0)
                break;
        }

        QStandardItemModel *remodel = (QStandardItemModel *)ui->nowentrust->model();

        QStandardItem *c9 = new QStandardItem(QString::number(nmodel->index(rownum,9).data().toInt()+reply.orderqty()));
        remodel->QStandardItemModel::setItem(rownum,9,c9);
        QStandardItem *c10 = new QStandardItem(QString::number(nmodel->index(rownum,8).data().toInt()-nmodel->index(rownum,9).data().toInt()));
        remodel->QStandardItemModel::setItem(rownum,10,c10);

        //insert to deal
        QStandardItemModel *model = (QStandardItemModel *)ui->deal->model();
        int dnum = model->rowCount();
        QStandardItem *i0 = new QStandardItem(QString::fromStdString(reply.transacttime()));
        QStandardItem *i1 = new QStandardItem(QString::fromStdString(reply.orderid()));
        QStandardItem *i2 = new QStandardItem(QString::fromStdString(reply.symbol()));
        QStandardItem *i3 = new QStandardItem(QString::fromStdString(tutorial::SideEnum_Name(reply.side())));
        QStandardItem *i4 = new QStandardItem(QString::number(reply.price()));
        QStandardItem *i5 = new QStandardItem(QString::number(reply.orderqty()));

        model->QStandardItemModel::setItem(dnum,0,i0);
        model->QStandardItemModel::setItem(dnum,1,i1);
        model->QStandardItemModel::setItem(dnum,2,i2);
        model->QStandardItemModel::setItem(dnum,3,i3);
        model->QStandardItemModel::setItem(dnum,4,i4);
        model->QStandardItemModel::setItem(dnum,5,i5);


    }
    else if(reply.orderstatus()==8)
    {
        QStandardItemModel *nmodel = (QStandardItemModel *)ui->nowentrust->model();
        for(int i=0;i<nmodel->rowCount();)
        {
            if(reply.orderid().compare(nmodel->index(i,1).data().toString().toStdString())==0)
            {
                QStandardItemModel *qmodel = (QStandardItemModel *)ui->passentrust->model();
                int qnum = qmodel->rowCount();
                QStandardItem *q0 = new QStandardItem(nmodel->index(i,0).data().toString());
                QStandardItem *q1 = new QStandardItem(nmodel->index(i,1).data().toString());
                QStandardItem *q2 = new QStandardItem(nmodel->index(i,2).data().toString());
                QStandardItem *q3 = new QStandardItem(nmodel->index(i,5).data().toString());
                QStandardItem *q4 = new QStandardItem(nmodel->index(i,6).data().toString());
                QStandardItem *q5 = new QStandardItem(nmodel->index(i,8).data().toString());
                QStandardItem *q6 = new QStandardItem(QString::fromStdString(tutorial::OrderStatusEnum_Name(reply.orderstatus())));
                QStandardItem *q7 = new QStandardItem(QString::fromStdString(reply.text()));

                qmodel->QStandardItemModel::setItem(qnum,0,q0);
                qmodel->QStandardItemModel::setItem(qnum,1,q1);
                qmodel->QStandardItemModel::setItem(qnum,2,q2);
                qmodel->QStandardItemModel::setItem(qnum,3,q3);
                qmodel->QStandardItemModel::setItem(qnum,4,q4);
                qmodel->QStandardItemModel::setItem(qnum,5,q5);
                qmodel->QStandardItemModel::setItem(qnum,6,q6);
                qmodel->QStandardItemModel::setItem(qnum,7,q7);

                nmodel->removeRow(i);
            }
            else
            {
                QStandardItemModel *model = (QStandardItemModel *)ui->nowentrust->model();

                QPushButton *bm = new QPushButton("Send");
                bm->setProperty("id",QString::number(i));
                bm->setProperty("action","modify");
                ui->nowentrust->setIndexWidget(model->index(i,12),bm);


                QPushButton *bd = new QPushButton("Delete");
                bd->setProperty("id",QString::number(i));
                bd->setProperty("action","delete");
                ui->nowentrust->setIndexWidget(model->index(i,13),bd);

                connect(bd,SIGNAL(clicked()),this,SLOT(delbuttonclick()));

                i++;
            }
        }

        QStandardItemModel *model = (QStandardItemModel *)ui->deal->model();
        int rownum = model->rowCount();
        QStandardItem *i0 = new QStandardItem(QString::fromStdString(reply.transacttime()));
        QStandardItem *i1 = new QStandardItem(QString::fromStdString(reply.orderid()));
        QStandardItem *i2 = new QStandardItem(QString::fromStdString(reply.symbol()));
        QStandardItem *i3 = new QStandardItem(QString::fromStdString(tutorial::SideEnum_Name(reply.side())));
        QStandardItem *i4 = new QStandardItem(QString::number(reply.price()));
        QStandardItem *i5 = new QStandardItem(QString::number(reply.orderqty()));

        model->QStandardItemModel::setItem(rownum,0,i0);
        model->QStandardItemModel::setItem(rownum,1,i1);
        model->QStandardItemModel::setItem(rownum,2,i2);
        model->QStandardItemModel::setItem(rownum,3,i3);
        model->QStandardItemModel::setItem(rownum,4,i4);
        model->QStandardItemModel::setItem(rownum,5,i5);

    }
    else if(reply.orderstatus()==11)
    {
        QStandardItemModel *model = (QStandardItemModel *)ui->passentrust->model();
        int rownum = model->rowCount();
        QStandardItem *i0 = new QStandardItem(QString::fromStdString(reply.transacttime()));
        QStandardItem *i1 = new QStandardItem(QString::fromStdString(reply.orderid()));
        QStandardItem *i2 = new QStandardItem(QString::fromStdString(reply.symbol()));
        QStandardItem *i3 = new QStandardItem(QString::fromStdString(tutorial::SideEnum_Name(reply.side())));
        QStandardItem *i4 = new QStandardItem(QString::number(reply.price()));
        QStandardItem *i5 = new QStandardItem(QString::number(reply.orderqty()));
        QStandardItem *i6 = new QStandardItem(QString::fromStdString(tutorial::OrderStatusEnum_Name(reply.orderstatus())));
        QStandardItem *i7 = new QStandardItem(QString::fromStdString(reply.text()));

        model->QStandardItemModel::setItem(rownum,0,i0);
        model->QStandardItemModel::setItem(rownum,1,i1);
        model->QStandardItemModel::setItem(rownum,2,i2);
        model->QStandardItemModel::setItem(rownum,3,i3);
        model->QStandardItemModel::setItem(rownum,4,i4);
        model->QStandardItemModel::setItem(rownum,5,i5);
        model->QStandardItemModel::setItem(rownum,6,i6);
        model->QStandardItemModel::setItem(rownum,7,i7);

    }
    //return;
}

void MainWindow::delbuttonclick()
{
    QMessageBox::StandardButton check = QMessageBox::warning(NULL,"Delete order","Delete this Order?",QMessageBox::Yes | QMessageBox::No);
    if(check == QMessageBox::No)
        return;
    QPushButton *btn =(QPushButton*)sender();
    int rownum = btn->property("id").toInt();
    //qDebug()<<rownum;
    /*timeval curtime;
    gettimeofday(&curtime,NULL);
    int milisec = curtime.tv_usec/1000;
    tm *local = localtime(&curtime.tv_sec);
    QString tempstr;
    tempstr.sprintf("%02d%02d%02d%03d%03d",local->tm_hour,local->tm_min,local->tm_sec,milisec,0);

    order.Clear();
    //1
    order.set_transacttime(tempstr.toStdString().c_str());
    //2
    if(ui->nowentrust->index(rownum,0).data().toString()==QString("sBuy"))
    {
        order.set_side(tutorial::SideEnum::sBuy);
    }
    else
    {
        order.set_side(tutorial::SideEnum::sSell);
    }

    //3
    order.set_symbol(ui->newscode->text().toStdString().c_str());
    //4
    order.set_orderqty(ui->newennum->text().toInt());
    //5
    double newprice = ui->newenprice->text().toDouble();
    //qDebug()<<"New Price : "<<newprice;
    order.set_price(newprice);
    //qDebug()<<"Set Price"<<order.price();
    //6
    if(ui->newortype->currentIndex()==0)
        order.set_ordertype(tutorial::OrderTypeEnum::otMarket);
    else
        order.set_ordertype(tutorial::OrderTypeEnum::otLimit);
    //7
    //order.set_tseordertype("");
    //8
    if(ui->newrequest->currentIndex()==0)
        order.set_timeinforce(tutorial::TimeInForceEnum::tifROD);
    else if(ui->newrequest->currentIndex()==1)
        order.set_timeinforce(tutorial::TimeInForceEnum::tifIOC);
    else
        order.set_timeinforce(tutorial::TimeInForceEnum::tifFOK);
    //9
    order.set_nid(129);
    //10
    if(ui->newmarket->currentIndex()==0)
    {
        if(ui->newentype->currentIndex()==0)
            order.set_market(tutorial::MarketEnum::mTSE);
        else
            order.set_market(tutorial::MarketEnum::mTSE_ODD);
    }
    else
    {
        if(ui->newentype->currentIndex()==0)
            order.set_market(tutorial::MarketEnum::mOTC);
        else
            order.set_market(tutorial::MarketEnum::mOTC_ODD);
    }
    //order.set_market(tutorial::MarketEnum::mFutures);
    //11
    order.set_orderid("0");
    //12
    order.set_kind(tutorial::KindEnum::kNew);

    emit senddata();*/
}

void MainWindow::serverfail(QString str)
{

    timeval curtime;
    gettimeofday(&curtime,NULL);
    int milisec = curtime.tv_usec/1000;
    tm *local = localtime(&curtime.tv_sec);
    QString tempstr;
    tempstr.sprintf("%02d:%02d:%02d.%03d",local->tm_hour,local->tm_min,local->tm_sec,milisec);
    ui->record->append(tempstr +" "+ str);
    QMessageBox::warning(NULL,"ERROR",str);
}
