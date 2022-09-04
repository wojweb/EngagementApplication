#include "keyreceiver.h"
#include "qcoreevent.h"
#include "qevent.h"
#include <iostream>
#include <QDebug>
#include "graphwindow.h"
#include <QBarSeries>


keyReceiver::keyReceiver(QBarSet* barset, QChartView *chartView, QString* names,
                         QLineEdit* winerEdit, QObject *parent)
    : QObject{parent}
{
    this->barSet = barset;
    this->chartView = chartView;
    this->sum = 0;
    this->winerEdit = winerEdit;
    for(int i = 0; i < barset->count(); i++)
    {
        this->names[i] = names[i];
        qDebug() << this->names[i];
    }
    for(int i = 0; i < 6; i++)
        this->clicked[i] = 0;

//    this->winerEdit->setText(this->names[1]);
}

bool keyReceiver::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type()==QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        qDebug() << "keypressed" << key->text() << this->sum;

        if (key->key()==Qt::Key_1)
            this->clicked[0]++;
        else if (key->key()==Qt::Key_2)
            this->clicked[1]++;
        else if (this->barSet->count() > 2 && key->key()==Qt::Key_3)
            this->clicked[2]++;
        else if (this->barSet->count() > 3 && key->key()==Qt::Key_4)
            this->clicked[3]++;
        else if (this->barSet->count() > 4 && key->key()==Qt::Key_5)
            this->clicked[4]++;
        else if (this->barSet->count() > 5 && key->key()==Qt::Key_6)
            this->clicked[5]++;
        else
           return QObject::eventFilter(obj, event);

        this->sum++;
        int maxIndex = 0;
        for(int i = 0; i < this->barSet->count(); i++)
        {
            this->barSet->replace(i, clicked[i] * 100 / (sum < 40 ? 40 : sum));
            if(this->clicked[i] > this->clicked[maxIndex])
                   maxIndex = i;
        }
        this->chartView->update();
        this->winerEdit->setText(this->names[maxIndex]);
        return true;
    } else {
        return QObject::eventFilter(obj, event);
    }
    return false;
}
