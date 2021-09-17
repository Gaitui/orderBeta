#include "showui.h"
showui::showui(QObject *parent) : QObject(parent){}

void showui::runui(int i)
{
    emit sendshow(i);
}
