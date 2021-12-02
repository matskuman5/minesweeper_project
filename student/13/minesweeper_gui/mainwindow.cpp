#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    board_size_ = 6;

    board_.init(0);

    init_squares();

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::square_click() {

    qDebug() << "test";

    for (QPushButton* pb : buttons_) {
        if (pb == sender()) {
            qDebug() << pb->objectName();

        }
    }

}

void MainWindow::init_squares() {

    central = new QWidget(this);
    gLayout = new QGridLayout(central);

    for (unsigned int x = 0; x < board_size_; x++) {
        for (unsigned int y = 0; y < board_size_; y++) {

            QString button_name = QString::fromStdString(std::to_string(x) + " " + std::to_string(y));

            QPushButton* pushButton = new QPushButton(this);

            pushButton->setObjectName(button_name);
            buttons_.push_back(pushButton);

            connect(pushButton, &QPushButton::clicked, this, &MainWindow::square_click);

            gLayout->addWidget(pushButton, y, x);

        }
    }

    setCentralWidget(central);

}
