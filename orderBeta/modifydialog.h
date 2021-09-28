#ifndef MODIFYDIALOG_H
#define MODIFYDIALOG_H
#include <QDialog>
#include <QComboBox>
#include <QGridLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <QtWidgets>
#include <QRegExp>

class modifydialog:public QDialog
{

public:
    modifydialog(QWidget *parent = 0);
    ~modifydialog();
    void setup(int,QString,QString,double,int);
    int rnum;
    QString bscode;
    QString bUID;
    double bprice;
    int bnum;
    QLabel *scodelabel;
    QLabel *uidlabel;
    QLabel *pricelabel;
    QLabel *numlabel;
    QComboBox typechoose;
    QLabel *modifylabel;
    QLineEdit modify;
    QPushButton sendbtn;
    QGridLayout *dialoglayout;
};

#endif // MODIFYDIALOG_H
