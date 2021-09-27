#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableView>
#include <QDebug>
#include <QThread>
#include <queue>
#include <QMessageBox>
#include <QLineEdit>
#include <sys/time.h>
#include <QCloseEvent>
#include "google/protobuf/text_format.h"
#include "SimulatorTradeProtos.pb.h"
#include <sstream>
#include <QPushButton>
#include <QAbstractItemView>
#include <unistd.h>
#include "addtrackdialog.h"
#include "data.h"
#include "format06.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void getshow(int num);
    void showError(QString);
    void on_sendNew_clicked();
    void relogin();
    void fromtcp(tutorial::SimulatorTradeReply);
    void delbuttonclick();
    void serverfail(QString);
    void on_addTrack_clicked();
    void getaddtrack();
    void deltrack();
    void getnewtrack(Data);
signals:
    void sendlink(QString);
    void senddata(tutorial::SimulatorTradeOrder);
    void linktoserver();
    void sendEnd();
    void udpEnd();
private:
    Ui::MainWindow *ui;
    addTrackDialog newtrack;
};

#endif // MAINWINDOW_H
