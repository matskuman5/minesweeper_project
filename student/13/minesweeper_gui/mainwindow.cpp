#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <string>
#include <QToolButton>

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

    for (QToolButton* tb : buttons_) {
        if (tb == sender()) {

            qDebug() << tb->objectName();

            std::string coordinates = tb->objectName().toStdString();

            //note: will have to change this to support boards over 9x9
            int x = coordinates.at(0) - '0';
            int y = coordinates.at(2) - '0';

            Square s = board_.getSquare(x, y);

            if (board_.openSquare(x, y)) {
                tb->setText(QString::number(s.countAdjacent()));
            } else {
                tb->setText("*");
            }

            qDebug() << board_.openSquare(x, y);
            qDebug() << tb->sizeHint();
            qDebug() << tb->sizePolicy();

            tb->setDisabled(true);

        }
    }

}

void MainWindow::init_squares() {

    central = new QWidget(this);
    gLayout = new QGridLayout(central);
    gLayout->setSpacing(3);

    for (unsigned int x = 0; x < board_size_; x++) {
        for (unsigned int y = 0; y < board_size_; y++) {

            QString button_name = QString::fromStdString(std::to_string(x) + " " + std::to_string(y));

            QToolButton* toolButton = new QToolButton(this);
            toolButton->setObjectName(button_name);

            //set the SizePolicy of the button to Expanding so it resizes properly
            QSizePolicy* sp = new QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            toolButton->setSizePolicy(*sp);

            buttons_.push_back(toolButton);

            connect(toolButton, &QToolButton::clicked, this, &MainWindow::square_click);

            gLayout->addWidget(toolButton, y, x);

        }
    }

    setCentralWidget(central);

}
