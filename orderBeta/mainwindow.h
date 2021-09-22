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
    void on_exit_clicked();
    void getshow(int num);
    void on_login_clicked();
    void showError(QString);

    void on_sendNew_clicked();

signals:
    void sendlink(QString);
    void sendlogin();
    void senddata();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
