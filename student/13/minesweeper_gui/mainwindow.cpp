#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    board_size_ = 6;

    board_.init(0);

    init_squares();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_squares() {

    central = new QWidget(this);
    gLayout = new QGridLayout(central);

    for (unsigned int x = 0; x < board_size_; x++) {
        for (unsigned int y = 0; y < board_size_; y++) {

            QPushButton* pushButton = new QPushButton(this);
            buttons_.push_back(pushButton);

            gLayout->addWidget(pushButton, y, x);

        }
    }

    setCentralWidget(central);

}
