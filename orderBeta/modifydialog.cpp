#include "modifydialog.h"

modifydialog::modifydialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("修改");
    resize(220,180);

    scodelabel = new QLabel;
    scodelabel->setText(bscode);
    QHBoxLayout *scodelayout = new QHBoxLayout;
    scodelayout->addWidget(new QLabel("商品代號"));
    scodelayout->addWidget(scodelabel);

    uidlabel = new QLabel;
    uidlabel->setText(bUID);
    QHBoxLayout *UIDlayout = new QHBoxLayout;
    UIDlayout->addWidget(new QLabel("單號"));
    UIDlayout->addWidget(uidlabel);

    pricelabel = new QLabel;
    pricelabel->setText(QString::number(bprice,'d',2));
    QHBoxLayout *pricelayout = new QHBoxLayout;
    pricelayout->addWidget(new QLabel("原本價格"));
    pricelayout->addWidget(pricelabel);

    numlabel = new QLabel;
    numlabel->setText(QString::number(bnum));
    QHBoxLayout *numlayout = new QHBoxLayout;
    numlayout->addWidget(new QLabel("數量"));
    numlayout->addWidget(numlabel);

    QHBoxLayout *typelayout = new QHBoxLayout;
    typechoose.addItem("價格",0);
    typechoose.addItem("數量",1);
    typelayout->addWidget(new QLabel("選擇修改"));
    typelayout->addWidget(&typechoose);


    modifylabel = new QLabel;
    modifylabel->setText("修改值");
    QRegExp doublerx("[0-9]{0,6}[\.][0-9]{0,2}");
    modify.setValidator(new QRegExpValidator(doublerx,this));
    QHBoxLayout *modifylayout = new QHBoxLayout;
    modifylayout->addWidget(modifylabel);
    modifylayout->addWidget(&modify);
    modifylayout->setStretchFactor(modifylabel,100);
    modifylayout->setStretchFactor(&modify,99);

    sendbtn.setText("確認送出");
    QHBoxLayout *btnlayout = new QHBoxLayout;
    btnlayout->addStretch(15);
    btnlayout->addWidget(&sendbtn);
    btnlayout->addStretch(15);

    dialoglayout = new QGridLayout;
    dialoglayout->setHorizontalSpacing(5);
    dialoglayout->addItem(scodelayout,0,0);
    dialoglayout->addItem(UIDlayout,1,0);
    dialoglayout->addItem(pricelayout,2,0);
    dialoglayout->addItem(numlayout,3,0);
    dialoglayout->addItem(typelayout,4,0);
    dialoglayout->addItem(modifylayout,5,0);
    dialoglayout->addItem(new QSpacerItem(20,20),6,0);
    dialoglayout->addItem(btnlayout,7,0);


    setLayout(dialoglayout);
}
modifydialog::~modifydialog(){}
void modifydialog::setup(int rownum,QString scode,QString UID,double pprice,int pnum)
{
    bscode.clear();
    bUID.clear();
    rnum = rownum;
    bscode.append(scode);
    bUID.append(UID);
    bprice = pprice;
    bnum = pnum;

    scodelabel->setText(bscode);
    uidlabel->setText(bUID);
    pricelabel->setText(QString::number(bprice,'d',2));
    numlabel->setText(QString::number(bnum));
}
