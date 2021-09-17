#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "showui.h"

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

signals:
    void sendlink(QString);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
