#include "mainwindow.h"
#include "ui_mainwindow.h"



extern bool havelogin;
extern std::string logindata;
extern bool shutdown;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //qDebug()<<"Mainwindow thread ID : "<<QThread::currentThreadId();

    connect(&newtrack.okbtn,SIGNAL(clicked()),this,SLOT(getaddtrack()));

    //set realtime
    QStandardItemModel *rmodel = new QStandardItemModel(0,12,this);
    rmodel->setHorizontalHeaderItem(0,new QStandardItem(QString("時間")));
    rmodel->setHorizontalHeaderItem(1,new QStandardItem(QString("商品代號")));
    rmodel->setHorizontalHeaderItem(2,new QStandardItem(QString("市場")));
    rmodel->setHorizontalHeaderItem(3,new QStandardItem(QString("漲停價")));
    rmodel->setHorizontalHeaderItem(4,new QStandardItem(QString("跌停價")));
    rmodel->setHorizontalHeaderItem(5,new QStandardItem(QString("成交量")));
    rmodel->setHorizontalHeaderItem(6,new QStandardItem(QString("成交價")));
    rmodel->setHorizontalHeaderItem(7,new QStandardItem(QString("買進張數")));
    rmodel->setHorizontalHeaderItem(8,new QStandardItem(QString("買進價格")));
    rmodel->setHorizontalHeaderItem(9,new QStandardItem(QString("賣出張數")));
    rmodel->setHorizontalHeaderItem(10,new QStandardItem(QString("賣出價格")));
    rmodel->setHorizontalHeaderItem(11,new QStandardItem(QString("")));
    ui->realtime->setModel(rmodel);

    //set nowentrust
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

    //set deal
    QStandardItemModel *dmodel = new QStandardItemModel(0,7,this);
    dmodel->setHorizontalHeaderItem(0,new QStandardItem(QString("時間")));
    dmodel->setHorizontalHeaderItem(1,new QStandardItem(QString("單號")));
    dmodel->setHorizontalHeaderItem(2,new QStandardItem(QString("商品代號")));
    dmodel->setHorizontalHeaderItem(3,new QStandardItem(QString("市場")));
    dmodel->setHorizontalHeaderItem(4,new QStandardItem(QString("買賣")));
    dmodel->setHorizontalHeaderItem(5,new QStandardItem(QString("成交價")));
    dmodel->setHorizontalHeaderItem(6,new QStandardItem(QString("成交數")));
    ui->deal->setModel(dmodel);

    //set passentrust
    QStandardItemModel *hmodel = new QStandardItemModel(0,10,this);
    hmodel->setHorizontalHeaderItem(0,new QStandardItem(QString("時間")));
    hmodel->setHorizontalHeaderItem(1,new QStandardItem(QString("單號")));
    hmodel->setHorizontalHeaderItem(2,new QStandardItem(QString("商品代號")));
    hmodel->setHorizontalHeaderItem(3,new QStandardItem(QString("市場")));
    hmodel->setHorizontalHeaderItem(4,new QStandardItem(QString("委託條件")));
    hmodel->setHorizontalHeaderItem(5,new QStandardItem(QString("買賣")));
    hmodel->setHorizontalHeaderItem(6,new QStandardItem(QString("委託價")));
    hmodel->setHorizontalHeaderItem(7,new QStandardItem(QString("數量")));
    hmodel->setHorizontalHeaderItem(8,new QStandardItem(QString("狀態")));
    hmodel->setHorizontalHeaderItem(9,new QStandardItem(QString("原因")));
    ui->passentrust->setModel(hmodel);

    //set newoder
    ui->newmarket->addItem("上市/整股",0);
    ui->newmarket->addItem("上市/零股",1);
    ui->newmarket->addItem("上櫃/整股",2);
    ui->newmarket->addItem("上櫃/零股",3);

    ui->newortype->addItem("市價",0);
    ui->newortype->addItem("限價",1);

    ui->newrequest->addItem("ROD",0);
    ui->newrequest->addItem("IOC",1);
    ui->newrequest->addItem("FOK",2);

    ui->newbuysell->addItem("買",0);
    ui->newbuysell->addItem("賣",1);

    //set number range
    QRegExp doublerx("[0-9]{0,6}[\.][0-9]{0,2}");
    ui->newenprice->setValidator(new QRegExpValidator(doublerx,this));

    ui->newennum->setValidator(new QIntValidator(1,1e9,this));

    ui->sendNew->setEnabled(false);

}

MainWindow::~MainWindow()
{
    //qDebug()<<"Mainwindow shut down";
    delete ui;
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
    ui->sendNew->setEnabled(true);
}

void MainWindow::on_sendNew_clicked()
{
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

    tutorial::SimulatorTradeOrder order;
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
    qDebug()<<"Set Price"<<order.price();
    //6
    if(ui->newortype->currentIndex()==0)
        order.set_ordertype(tutorial::OrderTypeEnum::otMarket);
    else
        order.set_ordertype(tutorial::OrderTypeEnum::otLimit);
    //7
    order.set_tseordertype("");
    //8
    if(ui->newrequest->currentIndex()==0)
        order.set_timeinforce(tutorial::TimeInForceEnum::tifROD);
    else if(ui->newrequest->currentIndex()==1)
        order.set_timeinforce(tutorial::TimeInForceEnum::tifIOC);
    else
        order.set_timeinforce(tutorial::TimeInForceEnum::tifFOK);
    //9
    order.set_nid(55);
    //10
    if(ui->newmarket->currentIndex()==0)
    {
        qDebug()<<"set Market = mtse";
        order.set_market(tutorial::MarketEnum::mTSE);
    }
    else if(ui->newmarket->currentIndex()==1)
    {
        qDebug()<<"set Market = mtse_ODD";
        order.set_market(tutorial::MarketEnum::mTSE_ODD);
    }
    else if(ui->newmarket->currentIndex()==2)
    {
        qDebug()<<"set Market = mOTC";
        order.set_market(tutorial::MarketEnum::mOTC);
    }
    else if(ui->newmarket->currentIndex()==3)
    {
        qDebug()<<"set Market = mOTC_ODD";
        order.set_market(tutorial::MarketEnum::mOTC_ODD);
    }
    //11
    order.set_orderid("0");
    //12
    order.set_kind(tutorial::KindEnum::kNew);

    qDebug()<<"market set : "<<order.market();
    emit senddata(order);
}

void MainWindow::fromtcp(tutorial::SimulatorTradeReply reply)
{
    if(reply.orderstatus()==2)
    {

        //add nowentrust
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
        //modify nowentrust
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
        QStandardItem *i3 = new QStandardItem(QString::fromStdString(tutorial::MarketEnum_Name(reply.market())));
        QStandardItem *i4 = new QStandardItem(QString::fromStdString(tutorial::SideEnum_Name(reply.side())));
        QStandardItem *i5 = new QStandardItem(QString::number(reply.price()));
        QStandardItem *i6 = new QStandardItem(QString::number(reply.orderqty()));

        model->QStandardItemModel::setItem(dnum,0,i0);
        model->QStandardItemModel::setItem(dnum,1,i1);
        model->QStandardItemModel::setItem(dnum,2,i2);
        model->QStandardItemModel::setItem(dnum,3,i3);
        model->QStandardItemModel::setItem(dnum,4,i4);
        model->QStandardItemModel::setItem(dnum,5,i5);
        model->QStandardItemModel::setItem(dnum,6,i6);


    }
    else if(reply.orderstatus()==8)
    {
        //add passentrust from now entrust
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
                QStandardItem *q3 = new QStandardItem(nmodel->index(i,3).data().toString());
                QStandardItem *q4 = new QStandardItem(nmodel->index(i,4).data().toString());
                QStandardItem *q5 = new QStandardItem(nmodel->index(i,5).data().toString());
                QStandardItem *q6 = new QStandardItem(nmodel->index(i,6).data().toString());
                QStandardItem *q7 = new QStandardItem(nmodel->index(i,8).data().toString());
                QStandardItem *q8 = new QStandardItem(QString::fromStdString(tutorial::OrderStatusEnum_Name(reply.orderstatus())));
                QStandardItem *q9 = new QStandardItem(QString::fromStdString(reply.text()));

                qmodel->QStandardItemModel::setItem(qnum,0,q0);
                qmodel->QStandardItemModel::setItem(qnum,1,q1);
                qmodel->QStandardItemModel::setItem(qnum,2,q2);
                qmodel->QStandardItemModel::setItem(qnum,3,q3);
                qmodel->QStandardItemModel::setItem(qnum,4,q4);
                qmodel->QStandardItemModel::setItem(qnum,5,q5);
                qmodel->QStandardItemModel::setItem(qnum,6,q6);
                qmodel->QStandardItemModel::setItem(qnum,7,q7);
                qmodel->QStandardItemModel::setItem(qnum,8,q8);
                qmodel->QStandardItemModel::setItem(qnum,9,q9);

                nmodel->removeRow(i);
            }
            else
            {
                //reset btn
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

        //add deal
        QStandardItemModel *model = (QStandardItemModel *)ui->deal->model();
        int rownum = model->rowCount();
        QStandardItem *i0 = new QStandardItem(QString::fromStdString(reply.transacttime()));
        QStandardItem *i1 = new QStandardItem(QString::fromStdString(reply.orderid()));
        QStandardItem *i2 = new QStandardItem(QString::fromStdString(reply.symbol()));
        QStandardItem *i3 = new QStandardItem(QString::fromStdString(tutorial::MarketEnum_Name(reply.market())));
        QStandardItem *i4 = new QStandardItem(QString::fromStdString(tutorial::SideEnum_Name(reply.side())));
        QStandardItem *i5 = new QStandardItem(QString::number(reply.price()));
        QStandardItem *i6 = new QStandardItem(QString::number(reply.orderqty()));

        model->QStandardItemModel::setItem(rownum,0,i0);
        model->QStandardItemModel::setItem(rownum,1,i1);
        model->QStandardItemModel::setItem(rownum,2,i2);
        model->QStandardItemModel::setItem(rownum,3,i3);
        model->QStandardItemModel::setItem(rownum,4,i4);
        model->QStandardItemModel::setItem(rownum,5,i5);
        model->QStandardItemModel::setItem(rownum,6,i6);

    }
    else if(reply.orderstatus()==11)
    {
        //add passentrust
        QStandardItemModel *model = (QStandardItemModel *)ui->passentrust->model();
        int rownum = model->rowCount();
        QStandardItem *i0 = new QStandardItem(QString::fromStdString(reply.transacttime()));
        QStandardItem *i1 = new QStandardItem(QString::fromStdString(reply.orderid()));
        QStandardItem *i2 = new QStandardItem(QString::fromStdString(reply.symbol()));
        QStandardItem *i3 = new QStandardItem(QString::fromStdString(tutorial::MarketEnum_Name(reply.market())));
        QStandardItem *i4 = new QStandardItem(QString::fromStdString(tutorial::TimeInForceEnum_Name(reply.timeinforce())));
        QStandardItem *i5 = new QStandardItem(QString::fromStdString(tutorial::SideEnum_Name(reply.side())));
        QStandardItem *i6 = new QStandardItem(QString::number(reply.price()));
        QStandardItem *i7 = new QStandardItem(QString::number(reply.orderqty()));
        QStandardItem *i8 = new QStandardItem(QString::fromStdString(tutorial::OrderStatusEnum_Name(reply.orderstatus())));
        QStandardItem *i9 = new QStandardItem(QString::fromStdString(reply.text()));

        model->QStandardItemModel::setItem(rownum,0,i0);
        model->QStandardItemModel::setItem(rownum,1,i1);
        model->QStandardItemModel::setItem(rownum,2,i2);
        model->QStandardItemModel::setItem(rownum,3,i3);
        model->QStandardItemModel::setItem(rownum,4,i4);
        model->QStandardItemModel::setItem(rownum,5,i5);
        model->QStandardItemModel::setItem(rownum,6,i6);
        model->QStandardItemModel::setItem(rownum,7,i7);
        model->QStandardItemModel::setItem(rownum,8,i8);
        model->QStandardItemModel::setItem(rownum,9,i9);

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
    ui->record->append(tempstr +" "+ str +" try again in 5s.");
    ui->sendNew->setEnabled(false);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton btn=QMessageBox::information(NULL,"Close","Close Program?",QMessageBox::Yes | QMessageBox::No);
    if(btn == QMessageBox::No)
    {
        event->ignore();
    }
    else if(btn == QMessageBox::Yes)
    {
        //qDebug()<<"Shut down";
        shutdown = true;
        emit sendEnd();
        emit udpEnd();
        event->accept();
    }
}

void MainWindow::on_addTrack_clicked()
{
    newtrack.exec();
}

void MainWindow::getaddtrack()
{
    if(newtrack.addscode.text().size()==0)
    {
        showError("Need Stock Code!");
    }
    else
    {
        //find exist in realtime
        QStandardItemModel *rmodel = (QStandardItemModel *)ui->realtime->model();
        bool newread = true;
        for(int i=0;i<rmodel->rowCount();i++)
        {
            if(newtrack.addscode.text().compare(rmodel->index(i,1).data().toString())==0)
            {
                if((rmodel->index(i,2).data().toString().compare("mTSE")==0 && newtrack.addmarket.currentIndex()==0)
                 ||(rmodel->index(i,2).data().toString().compare("mOTC")==0 && newtrack.addmarket.currentIndex()==1)
                 ||(rmodel->index(i,2).data().toString().compare("mTSE_ODD")==0 && newtrack.addmarket.currentIndex()==2)
                 ||(rmodel->index(i,2).data().toString().compare("mOTC_ODD")==0 && newtrack.addmarket.currentIndex()==3))
                {
                    newread =false;
                    break;
                }
            }
        }
        //add realtime
        newtrack.accept();
        if(newread)
        {
            int rnum = rmodel->rowCount();
            QStandardItem *r1 = new QStandardItem(newtrack.addscode.text());
            QStandardItem *r2;
            if(newtrack.addmarket.currentIndex()==0)
                r2= new QStandardItem("mTSE");
            else if(newtrack.addmarket.currentIndex()==1)
                r2 = new QStandardItem("mTSE_ODD");
            else if(newtrack.addmarket.currentIndex()==2)
                r2 = new QStandardItem("mOTC");
            else if(newtrack.addmarket.currentIndex()==3)
                r2 = new QStandardItem("mOTC_ODD");

            rmodel->QStandardItemModel::setItem(rnum,1,r1);
            rmodel->QStandardItemModel::setItem(rnum,2,r2);

            QPushButton *btn = new QPushButton("Delete");
            btn->setProperty("id",rnum);
            btn->setProperty("action","delete");

            connect(btn,SIGNAL(clicked()),this,SLOT(deltrack()));
            ui->realtime->setIndexWidget(rmodel->index(rnum,11),btn);
        }
        else
        {
            QMessageBox::information(NULL,"Information","Already Track!");
        }

    }
}

void MainWindow::deltrack()
{
    QMessageBox::StandardButton checkbtn=QMessageBox::information(NULL,"Delete track","Delete this track?",QMessageBox::Yes | QMessageBox::No);
    if(checkbtn == QMessageBox::Yes)
    {
        QPushButton *btn = (QPushButton *)sender();
        QStandardItemModel *rmodel = (QStandardItemModel *)ui->realtime->model();
        rmodel->removeRow(btn->property("id").toInt());
        for(int i=btn->property("id").toInt();i<rmodel->rowCount();i++)
        {
            QPushButton *btn = new QPushButton("Delete");
            btn->setProperty("id",i);
            btn->setProperty("action","delete");

            connect(btn,SIGNAL(clicked()),this,SLOT(deltrack()));
            ui->realtime->setIndexWidget(rmodel->index(i,11),btn);
        }
    }
}

void MainWindow::getnewtrack(Data newdata)
{
    QStandardItemModel *rmodel = (QStandardItemModel *)ui->realtime->model();
    if(newdata.dhead.mcode==1)
    {
        if(newdata.dhead.mtype==1)
        {
            //qDebug()<<"New 01 BB";
            tseFormat01 new01;
            new01.decodetse01(newdata.pkt_data,newdata.dhead);
            //qDebug()<<"01 scode : "<<QString::fromStdString(new01.scode);
            for(int i=0;i<rmodel->rowCount();i++)
            {
                if(new01.scode.compare(rmodel->index(i,1).data().toString().toStdString())==0 &&
                    rmodel->index(i,2).data().toString().compare("mTSE")==0)
                {
                    //qDebug()<<"New 01 CC";
                    QStandardItem *r3 = new QStandardItem(QString::number(new01.limup,'d',4));
                    QStandardItem *r4 = new QStandardItem(QString::number(new01.limdown,'d',4));
                    rmodel->QStandardItemModel::setItem(i,3,r3);
                    rmodel->QStandardItemModel::setItem(i,4,r4);
                    break;
                }
            }
        }
        else if(newdata.dhead.mtype==2)
        {
            otcformat01 new01;
            new01.decodeotc01(newdata.pkt_data,newdata.dhead);
            qDebug()<<"01 scode : "<<QString::fromStdString(new01.scode);
            for(int i=0;i<rmodel->rowCount();i++)
            {
                if(new01.scode.compare(rmodel->index(i,1).data().toString().toStdString())==0 &&
                    rmodel->index(i,2).data().toString().compare("mTSE")==0)
                {
                    //qDebug()<<"New 01 CC";
                    QStandardItem *r3 = new QStandardItem(QString::number(new01.limup,'d',4));
                    QStandardItem *r4 = new QStandardItem(QString::number(new01.limdown,'d',4));
                    rmodel->QStandardItemModel::setItem(i,3,r3);
                    rmodel->QStandardItemModel::setItem(i,4,r4);
                    break;
                }
            }
        }
    }
    else if(newdata.dhead.mcode==6)
    {
        //qDebug()<<"BB";
        format06 new06;
        new06.decode06(newdata.pkt_data,newdata.dhead);
        //qDebug()<<QString::fromStdString(new06.scode);
        for(int i=0;i<rmodel->rowCount();i++)
        {
            if(new06.scode.compare(rmodel->index(i,1).data().toString().toStdString())==0 &&
               ((rmodel->index(i,2).data().toString().compare("mTSE")==0 && new06.dhead.mtype==1) ||
                (rmodel->index(i,2).data().toString().compare("mOTC")==0 && new06.dhead.mtype==2)))
            {
                //qDebug()<<"CC";
                QString tracktime;
                tracktime.sprintf("%02d:%02d:%02d.%03d.%03d",new06.mtime[0],new06.mtime[1],new06.mtime[2],new06.mtime[3]*10+new06.mtime[4]/10,(new06.mtime[4]%10)*100+new06.mtime[5]);
                QStandardItem *r0 = new QStandardItem(tracktime);
                rmodel->QStandardItemModel::setItem(i,0,r0);
                int j=0;
                if(new06.reveal[0]==1)
                {
                    QStandardItem *r5 = new QStandardItem(QString::number(new06.rnum[j]));
                    QStandardItem *r6 = new QStandardItem(QString::number(new06.rprice[j],'d',4));
                    rmodel->QStandardItemModel::setItem(i,5,r5);
                    rmodel->QStandardItemModel::setItem(i,6,r6);
                    j++;
                }
                int tbuy=0;
                for(int k=1;k<4;k++)
                    tbuy=(tbuy<<1)+new06.reveal[k];
                qDebug()<<tbuy;
                if(tbuy!=0)
                {
                    QStandardItem *r7 = new QStandardItem(QString::number(new06.rnum[j]));
                    QStandardItem *r8 = new QStandardItem(QString::number(new06.rprice[j],'d',4));
                    rmodel->QStandardItemModel::setItem(i,7,r7);
                    rmodel->QStandardItemModel::setItem(i,8,r8);
                    j+=tbuy;
                }
                int tsell=0;
                for(int k=4;k<7;k++)
                    tsell=(tsell<<1)+new06.reveal[k];
                qDebug()<<tsell;
                if(tsell!=0)
                {
                    QStandardItem *r9 = new QStandardItem(QString::number(new06.rnum[j]));
                    QStandardItem *r10 = new QStandardItem(QString::number(new06.rprice[j],'d',4));
                    rmodel->QStandardItemModel::setItem(i,9,r9);
                    rmodel->QStandardItemModel::setItem(i,10,r10);
                    j+=tbuy;
                }
                break;
            }
        }
    }
    else if(newdata.dhead.mcode==23)
    {
        //qDebug()<<"23 BB";
        format23 new23;
        new23.decode23(newdata.pkt_data,newdata.dhead);
        qDebug()<<"23 BB : "<<QString::fromStdString(new23.scode);
        for(int i=0;i<rmodel->rowCount();i++)
        {
            if(new23.scode.compare(rmodel->index(i,1).data().toString().toStdString())==0 &&
               ((rmodel->index(i,2).data().toString().compare("mTSE_ODD")==0 && new23.dhead.mtype==1) ||
                (rmodel->index(i,2).data().toString().compare("mOTC_ODD")==0 && new23.dhead.mtype==2)))
            {
                //qDebug()<<"CC";
                QString tracktime;
                tracktime.sprintf("%02d:%02d:%02d.%03d.%03d",new23.mtime[0],new23.mtime[1],new23.mtime[2],new23.mtime[3]*10+new23.mtime[4]/10,(new23.mtime[4]%10)*100+new23.mtime[5]);
                QStandardItem *r0 = new QStandardItem(tracktime);
                rmodel->QStandardItemModel::setItem(i,0,r0);
                int j=0;
                if(new23.reveal[0]==1)
                {
                    QStandardItem *r5 = new QStandardItem(QString::number(new23.rnum[j]));
                    QStandardItem *r6 = new QStandardItem(QString::number(new23.rprice[j],'d',4));
                    rmodel->QStandardItemModel::setItem(i,5,r5);
                    rmodel->QStandardItemModel::setItem(i,6,r6);
                    j++;
                }
                int tbuy=0;
                for(int k=1;k<4;k++)
                    tbuy=(tbuy<<1)+new23.reveal[k];
                qDebug()<<tbuy;
                if(tbuy!=0)
                {
                    QStandardItem *r7 = new QStandardItem(QString::number(new23.rnum[j]));
                    QStandardItem *r8 = new QStandardItem(QString::number(new23.rprice[j],'d',4));
                    rmodel->QStandardItemModel::setItem(i,7,r7);
                    rmodel->QStandardItemModel::setItem(i,8,r8);
                    j+=tbuy;
                }
                int tsell=0;
                for(int k=4;k<7;k++)
                    tsell=(tsell<<1)+new23.reveal[k];
                qDebug()<<tsell;
                if(tsell!=0)
                {
                    QStandardItem *r9 = new QStandardItem(QString::number(new23.rnum[j]));
                    QStandardItem *r10 = new QStandardItem(QString::number(new23.rprice[j],'d',4));
                    rmodel->QStandardItemModel::setItem(i,9,r9);
                    rmodel->QStandardItemModel::setItem(i,10,r10);
                    j+=tbuy;
                }
                break;
            }
        }
    }

}

