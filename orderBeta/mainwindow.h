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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void getshow(int num);
    void showError(QString);
    void on_sendNew_clicked();
    void relogin();
    void fromtcp();
    void delbuttonclick();
    void serverfail(QString);

signals:
    void sendlink(QString);
    void sendlogin();
    void senddata();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
