#ifndef SHOWUI_H
#define SHOWUI_H
#include <QDebug>
#include <QObject>

class showui : public QObject
{

    Q_OBJECT
public:
    explicit showui(QObject *parent = 0);
    void runui(int i);
signals:
    void sendshow(int i);
private slots:

};

#endif // SHOWUI_H
