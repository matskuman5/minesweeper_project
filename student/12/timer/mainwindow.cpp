#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = &timer_object;
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(step()));

    min = 0;
    sec = 0;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::step()
{

    if (ui->lcdNumberSec->value() == 59) {
        min += 1;
        sec = 0;
    } else {
        sec += 1;
    }

    ui->lcdNumberMin->display(min);
    ui->lcdNumberSec->display(sec);

}

void MainWindow::on_startButton_clicked()
{

    timer->start(1000);

}


void MainWindow::on_stopButton_clicked()
{

    timer->stop();

}


void MainWindow::on_resetButton_clicked()
{
    min = 0;
    sec = 0;
    ui->lcdNumberMin->display(min);
    ui->lcdNumberSec->display(sec);
}

