#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SimulatorTradeProtos.pb.h"
#include "google/protobuf/text_format.h"
#include <sstream>


extern bool login;
extern std::queue<int> q;
extern tutorial::SimulatorTradeOrder order;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //showui *s = new showui(this);


    QStandardItemModel *rmodel = new QStandardItemModel(0,9,this);
    rmodel->setHorizontalHeaderItem(0,new QStandardItem(QString("時間")));
    rmodel->setHorizontalHeaderItem(1,new QStandardItem(QString("商品代號")));
    rmodel->setHorizontalHeaderItem(2,new QStandardItem(QString("市場")));
    rmodel->setHorizontalHeaderItem(3,new QStandardItem(QString("成交量")));
    rmodel->setHorizontalHeaderItem(4,new QStandardItem(QString("成交價")));
    rmodel->setHorizontalHeaderItem(5,new QStandardItem(QString("買進張數")));
    rmodel->setHorizontalHeaderItem(6,new QStandardItem(QString("買進價格")));
    rmodel->setHorizontalHeaderItem(7,new QStandardItem(QString("賣出張數")));
    rmodel->setHorizontalHeaderItem(8,new QStandardItem(QString("賣出價格")));
    ui->realtime->setModel(rmodel);

    QStandardItemModel *enmodel = new QStandardItemModel(0,11,this);
    enmodel->setHorizontalHeaderItem(0,new QStandardItem(QString("時間")));
    enmodel->setHorizontalHeaderItem(1,new QStandardItem(QString("單號")));
    enmodel->setHorizontalHeaderItem(2,new QStandardItem(QString("商品代號")));
    enmodel->setHorizontalHeaderItem(3,new QStandardItem(QString("委託條件")));
    enmodel->setHorizontalHeaderItem(4,new QStandardItem(QString("買賣")));
    enmodel->setHorizontalHeaderItem(5,new QStandardItem(QString("委託價")));
    enmodel->setHorizontalHeaderItem(6,new QStandardItem(QString("委託數")));
    enmodel->setHorizontalHeaderItem(7,new QStandardItem(QString("成交數")));
    enmodel->setHorizontalHeaderItem(8,new QStandardItem(QString("剩餘數")));
    enmodel->setHorizontalHeaderItem(9,new QStandardItem(QString("修改數")));
    enmodel->setHorizontalHeaderItem(10,new QStandardItem(QString("送出")));
    ui->nowentrust->setModel(enmodel);

    QStandardItemModel *dmodel = new QStandardItemModel(0,7,this);
    dmodel->setHorizontalHeaderItem(0,new QStandardItem(QString("時間")));
    dmodel->setHorizontalHeaderItem(1,new QStandardItem(QString("單號")));
    dmodel->setHorizontalHeaderItem(2,new QStandardItem(QString("商品代號")));
    dmodel->setHorizontalHeaderItem(3,new QStandardItem(QString("買賣")));
    dmodel->setHorizontalHeaderItem(4,new QStandardItem(QString("委託價")));
    dmodel->setHorizontalHeaderItem(5,new QStandardItem(QString("委託數")));
    dmodel->setHorizontalHeaderItem(6,new QStandardItem(QString("成交數")));

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

    if(login)
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

void MainWindow::on_sendNew_clicked()
{
    /*if(!login)
    {
        showError("Please login!");
        return;
    }*/
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
    QMessageBox::information(NULL,"Send new order","Send this New Order?",QMessageBox::Yes | QMessageBox::No);
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
    order.set_price(ui->newenprice->text().toDouble());
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
    //11
    order.set_orderid("0");
    //12
    order.set_kind(tutorial::KindEnum::kNew);

    emit senddata();
}
