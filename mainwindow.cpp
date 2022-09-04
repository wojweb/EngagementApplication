#include "mainwindow.h"
#include <iostream>
#include "./ui_mainwindow.h"
#include "graphwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(numOfUsersChanged(int)));

    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startButtonClicked()));
    numOfUsersChanged(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::numOfUsersChanged(int index)
{

    QLineEdit *lines[6];
    for(int i = 0; i < 6; i++)
    {
        QString lineName = "name_" + QString::number(i + 1);
        lines[i] = MainWindow::findChild<QLineEdit*>(lineName);

        if (i < index + 2)
        {
            lines[i]->setReadOnly(false);
            lines[i]->setStyleSheet("background-color:white");
        }
        else
        {
            lines[i]->setReadOnly(true);
            lines[i]->setStyleSheet("background-color:lightgrey");
            lines[i]->setText("");
        }
    }
}

void MainWindow::startButtonClicked()
{
    auto graphWindow = new GraphWindow(ui->comboBox->currentIndex()+2, this);
    graphWindow->show();
    hide();

}
