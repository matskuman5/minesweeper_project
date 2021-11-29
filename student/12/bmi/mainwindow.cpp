#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <string>
#include <cmath>
#include <iostream>

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


void MainWindow::on_countButton_clicked()
{

    ui->infoTextBrowser->clear();

    QString q_weight = ui->weightLineEdit->text();
    std::string s_weight = q_weight.toStdString();
    int weight = std::stoi(s_weight);

    QString q_height = ui->heightLineEdit->text();
    std::string s_height = q_height.toStdString();
    int height = std::stoi(s_height);
    double height_d = 1.0 * height;
    double height_cm = height_d / 100;

    if (height == 0) {
        ui->resultLabel->setText("");
        ui->infoTextBrowser->append("Cannot count");
    } else {

        qDebug() << weight << ", " << height_cm;

        double bmi = weight / std::pow(height_cm, 2);

        if (bmi < 18.5) {
            ui->infoTextBrowser->append("You are underweight");
        } else if (bmi < 25) {
            ui->infoTextBrowser->append("Your weight is normal");
        } else {
            ui->infoTextBrowser->append("You are overweight");
        }

        std::string s_bmi = std::to_string(bmi);
        QString q_bmi = QString::fromStdString(s_bmi);

        ui->resultLabel->setText(q_bmi);

    }

}

