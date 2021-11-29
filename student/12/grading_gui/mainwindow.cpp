#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gradecounter.hh"
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_countPushButton_clicked()
{

    ui->textBrowser->clear();

    int n = ui->spinBoxN->value();
    int g = ui->spinBoxG->value();
    int p = ui->spinBoxP->value();
    int e = ui->spinBoxE->value();

    int score = count_final_grade(n, g, p, e);
    std::string score_as_string = std::to_string(score);
    QString qstr = QString::fromStdString(score_as_string);

    ui->textBrowser->append("Total grade: " + qstr);

}

