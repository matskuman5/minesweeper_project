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

    central = new QWidget(this);
    setCentralWidget(central);
    main_grid = new QGridLayout(central);

    reset_button_ = new QPushButton("Reset", this);
    connect(reset_button_, &QPushButton::clicked, this, &MainWindow::reset_button_click);

    check_button_ = new QPushButton("Check", this);

    button_grid = new QGridLayout(central);
    button_grid->addWidget(reset_button_, 0, 0);
    button_grid->addWidget(check_button_, 0, 1);
    main_grid->addLayout(button_grid, 1, 0);

    board_grid = new QGridLayout();
    main_grid->addLayout(board_grid, 0, 0);
    board_grid->setSpacing(3);

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
//                end_game();
            }

            qDebug() << board_.openSquare(x, y);
            qDebug() << tb->sizeHint();
            qDebug() << tb->sizePolicy();

            tb->setDisabled(true);
        }
    }

}

void MainWindow::reset_button_click() {

    qDebug() << "reset";

    for (QToolButton* tb : buttons_) {
        delete tb;
    }
    buttons_.clear();


    init_squares();

}

//void MainWindow::end_game() {

//    for (QToolButton* tb : buttons_) {
//        tb->setDisabled(true);
//    }

//}

void MainWindow::init_squares() {

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

            board_grid->addWidget(toolButton, y, x);

        }
    }

}
