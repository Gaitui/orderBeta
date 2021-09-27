#include "addtrackdialog.h"

addTrackDialog::addTrackDialog(QWidget *parent):QDialog(parent)
{
    setWindowTitle("新增追蹤");
    resize(220,180);

    scodelabel.setText("商品代號");

    scodelayout = new QHBoxLayout;
    scodelayout->addWidget(&scodelabel);
    scodelayout->addWidget(&addscode);
    scodelayout->setStretchFactor(&scodelabel,100);
    scodelayout->setStretchFactor(&addscode,99);



    marketlabel.setText("市場");

    addmarket.addItem("上市/整股",0);
    addmarket.addItem("上市/零股",1);
    addmarket.addItem("上櫃/整股",2);
    addmarket.addItem("上櫃/零股",3);
    marketlayout = new QHBoxLayout;
    marketlayout->addWidget(&marketlabel);
    marketlayout->addWidget(&addmarket);


    okbtn.setText("新增");
    btnlayout = new QHBoxLayout;
    btnlayout->addStretch(15);
    btnlayout->addWidget(&okbtn);
    btnlayout->addStretch(15);

    addlayout = new QGridLayout;
    addlayout->addItem(scodelayout,0,0);
    addlayout->addItem(marketlayout,1,0);
    addlayout->addItem(new QSpacerItem(20,20),2,0);
    addlayout->addItem(btnlayout,3,0);


    setLayout(addlayout);

}

addTrackDialog::~addTrackDialog(){}
