#ifndef KEYRECEIVER_H
#define KEYRECEIVER_H

#include <QObject>
#include <QBarSet>
#include <QChartView>
#include <QLineEdit>

class keyReceiver : public QObject
{
    Q_OBJECT
public:
    explicit keyReceiver(QBarSet* barset, QChartView *chartView, QString* names,
    QLineEdit* winerEdit, QObject *parent = nullptr);

protected:
    QBarSet* barSet;
    QChartView *chartView;
    QString names[6];
    QLineEdit* winerEdit;

    int sum;
    int clicked[6];
    bool eventFilter(QObject* obj, QEvent* event);
signals:

};

#endif // KEYRECEIVER_H
