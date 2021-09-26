#ifndef ADDTRACKDIALOG_H
#define ADDTRACKDIALOG_H
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

class addTrackDialog : public QDialog
{
    //Q_OBJECT
public:
    addTrackDialog(QWidget *parent = 0);
    ~addTrackDialog();
    QLabel scodelabel;
    QLineEdit addscode;
    QHBoxLayout *scodelayout;
    QLabel marketlabel;
    QComboBox addmarket;
    QHBoxLayout *marketlayout;
    QPushButton okbtn;
    QHBoxLayout *btnlayout;
    QGridLayout *addlayout;
};

#endif // ADDTRACKDIALOG_H
