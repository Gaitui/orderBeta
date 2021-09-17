#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QTableView>
#include <QDebug>
#include <QThread>
#include <queue>

extern bool login;
extern std::queue<int> q;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //showui *s = new showui(this);



    QStandardItemModel *rmodel = new QStandardItemModel(0,6,this);
    rmodel->setHorizontalHeaderItem(0,new QStandardItem(QString("商品代號")));
    rmodel->setHorizontalHeaderItem(1,new QStandardItem(QString("市場")));
    rmodel->setHorizontalHeaderItem(2,new QStandardItem(QString("買進張數")));
    rmodel->setHorizontalHeaderItem(3,new QStandardItem(QString("買進價格")));
    rmodel->setHorizontalHeaderItem(4,new QStandardItem(QString("賣出價格")));
    rmodel->setHorizontalHeaderItem(5,new QStandardItem(QString("賣出張數")));
    ui->realtime->setModel(rmodel);

    QStandardItemModel *enmodel = new QStandardItemModel(0,9,this);
    enmodel->setHorizontalHeaderItem(0,new QStandardItem(QString("單號")));
    enmodel->setHorizontalHeaderItem(1,new QStandardItem(QString("商品代號")));
    enmodel->setHorizontalHeaderItem(2,new QStandardItem(QString("買賣")));
    enmodel->setHorizontalHeaderItem(3,new QStandardItem(QString("委託價")));
    enmodel->setHorizontalHeaderItem(4,new QStandardItem(QString("委託數")));
    enmodel->setHorizontalHeaderItem(5,new QStandardItem(QString("成交數")));
    enmodel->setHorizontalHeaderItem(6,new QStandardItem(QString("剩餘數")));
    enmodel->setHorizontalHeaderItem(7,new QStandardItem(QString("修改數")));
    enmodel->setHorizontalHeaderItem(8,new QStandardItem(QString("送出")));
    ui->nowentrust->setModel(enmodel);

    QStandardItemModel *dmodel = new QStandardItemModel(0,6,this);
    dmodel->setHorizontalHeaderItem(0,new QStandardItem(QString("單號")));
    dmodel->setHorizontalHeaderItem(1,new QStandardItem(QString("商品代號")));
    dmodel->setHorizontalHeaderItem(2,new QStandardItem(QString("買賣")));
    dmodel->setHorizontalHeaderItem(3,new QStandardItem(QString("委託價")));
    dmodel->setHorizontalHeaderItem(4,new QStandardItem(QString("委託數")));
    dmodel->setHorizontalHeaderItem(5,new QStandardItem(QString("成交數")));

    ui->deal->setModel(dmodel);

    QStandardItemModel *hmodel = new QStandardItemModel(0,7,this);
    hmodel->setHorizontalHeaderItem(0,new QStandardItem(QString("單號")));
    hmodel->setHorizontalHeaderItem(1,new QStandardItem(QString("商品代號")));
    hmodel->setHorizontalHeaderItem(2,new QStandardItem(QString("買賣")));
    hmodel->setHorizontalHeaderItem(3,new QStandardItem(QString("委託價")));
    hmodel->setHorizontalHeaderItem(4,new QStandardItem(QString("數量")));
    hmodel->setHorizontalHeaderItem(5,new QStandardItem(QString("狀態")));
    hmodel->setHorizontalHeaderItem(6,new QStandardItem(QString("原因")));
    ui->passentrust->setModel(hmodel);

    if(login)
    {
        ui->login->setEnabled(false);
        ui->logout->setEnabled(true);
        ui->user->setText("Hi!");
    }
    else
    {
        ui->login->setEnabled(true);
        ui->logout->setEnabled(false);
        ui->user->setText("Please login");
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
    QStandardItem *i0 = new QStandardItem(QString::number(k));
    QStandardItem *i1 = new QStandardItem("Market");
    QStandardItem *i2 = new QStandardItem("Buy Num "+QString::number(k));
    QStandardItem *i3 = new QStandardItem("Buy price "+QString::number(k));
    QStandardItem *i4 = new QStandardItem("Sell price "+QString::number(k));
    QStandardItem *i5 = new QStandardItem("Sell Num "+QString::number(k));

    rmodel->QStandardItemModel::setItem(rownum,0,i0);
    rmodel->QStandardItemModel::setItem(rownum,1,i1);
    rmodel->QStandardItemModel::setItem(rownum,2,i2);
    rmodel->QStandardItemModel::setItem(rownum,3,i3);
    rmodel->QStandardItemModel::setItem(rownum,4,i4);
    rmodel->QStandardItemModel::setItem(rownum,5,i5);

    return;
}

void MainWindow::on_login_clicked()
{
    QString str = "Test129";
    emit sendlink(str);
}
