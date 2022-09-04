#include "graphwindow.h"
#include "ui_graphwindow.h"
#include "mainwindow.h"
#include "keyreceiver.h"
#include <iostream>
#include <QDebug>

#include <QtCharts>


GraphWindow::GraphWindow(int numOfUsers, QWidget* firstWindow, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::graphWindow)
{
    ui->setupUi(this);

    this->firstWindow = firstWindow;
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(backButtonClicked()));

    QBarSet* barSet = new QBarSet("");
    QBarSeries* series = new QBarSeries();
    QStringList categories;
    QString names[6];
    for(int i = 0; i < numOfUsers; i++)
    {
        QString lineName = "name_" + QString::number(i + 1);
        auto lineEdit = firstWindow->findChild<QLineEdit*>(lineName);
        categories <<  lineEdit->text();
        names[i] = QString(lineEdit->text());
        *barSet << 0;
    }

    series->append(barSet);
    qDebug() << series->barSets().at(0)->at(0);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->markers(series)[0]->setVisible(false);
    chart->setTitle("Who and how is involved in the discussion. [%]");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,100);
    axisY->setTickInterval(10);
//    axisY->setLabelFormat("%");

    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);


    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

       QChartView *chartView = new QChartView(chart, ui->graphWidget);

//       chartView->setRenderHint(QPainter::Antialiasing);
       chartView->setFixedSize(ui->graphWidget->size());


       ui->graphWidget->setStyleSheet("background-color:grey");
//       setCentralWidget(chartView);

       keyReceiver* key = new keyReceiver(barSet, chartView, names,
                                          this->findChild<QLineEdit*>("winnerLine"));
       this->installEventFilter(key);


//       chartView->update();
}

GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::backButtonClicked()
{
    this->firstWindow->show();
    close();
}
