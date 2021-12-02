#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <string>
#include <QToolButton>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    board_size_ = 6;
    board_.init(0);

    central = new QWidget(this);
    setCentralWidget(central);
    main_grid = new QGridLayout(central);

    new_game_button_ = new QPushButton("New Game", this);
    connect(new_game_button_, &QPushButton::clicked, this, &MainWindow::new_game_button_click);

    check_button_ = new QPushButton("Check", this);

    seed_line_edit_ = new QLineEdit();
    seed_line_edit_->setPlaceholderText("Seed:");

    board_size_spinbox_ = new QSpinBox();
    board_size_spinbox_->setMinimum(2);
    board_size_label_ = new QLabel();
    board_size_label_->setText("Board size: (2-99)");

    text_browser_ = new QTextBrowser();

    timer_ = new QTimer(this);
    timer_->setInterval(1000);
    connect(timer_, &QTimer::timeout, this, &MainWindow::timer_tick);

    time_ = new QLabel(this);
    time_->setText("Time: 0:00");
    minutes_ = 0;
    seconds_ = 0;

    button_grid = new QGridLayout(central);
    button_grid->addWidget(new_game_button_, 0, 0);
    button_grid->addWidget(check_button_, 0, 1);
    button_grid->addWidget(seed_line_edit_, 1, 0);
    button_grid->addWidget(text_browser_, 2, 0);
    button_grid->addWidget(time_, 2, 1);
    button_grid->addWidget(board_size_label_, 1, 1);
    button_grid->addWidget(board_size_spinbox_, 1, 2);
    main_grid->addLayout(button_grid, 1, 0);

    text_browser_->append("Welcome! Enter a seed and press 'New Game' to begin!");

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
                if (board_.isGameOver()) {
                    end_game(true);
                }
            } else {
                tb->setText("*");
                end_game(false);
            }

            qDebug() << board_.openSquare(x, y);
            qDebug() << tb->sizeHint();
            qDebug() << tb->sizePolicy();

            tb->setDisabled(true);
        }
    }

}

void MainWindow::new_game_button_click() {

    for (QChar qc : seed_line_edit_->text()) {
        if (!qc.isDigit()) {
            text_browser_->append("Error: seed must be an integer value");
            return;
        }
    }

    if (seed_line_edit_->text().isEmpty()) {
        text_browser_->append("Error: empty seed");
        return;
    }

    qDebug() << "reset";

    for (QToolButton* tb : buttons_) {
        delete tb;
    }
    buttons_.clear();

    board_grid = new QGridLayout();
    main_grid->addLayout(board_grid, 0, 0);
    board_grid->setSpacing(3);

    init_squares();

    board_ = GameBoard();

    board_.init(seed_line_edit_->text().toInt());

    minutes_ = 0;
    seconds_ = 0;
    timer_->start();

}

void MainWindow::timer_tick() {

    if (seconds_ == 59) {
        minutes_++;
        seconds_ = 0;
    } else {
        seconds_++;
    }

    //this is to make sure we get a leading zero, e.g. "0:05" instead of "0:5"
    if (seconds_ < 10) {
        time_->setText("Time: " + QString::number(minutes_) + ":0" + QString::number(seconds_));
    } else {
        time_->setText("Time: " + QString::number(minutes_) + ":" + QString::number(seconds_));
    }

}

void MainWindow::end_game(bool won) {

    for (QToolButton* tb : buttons_) {
        tb->setDisabled(true);
    }

    timer_->stop();

    if (won) {
        text_browser_->append("You won, great job!");
    } else {
        text_browser_->append("BOOM! You lost!");
    }

    text_browser_->append("Game over! Enter a seed and press 'New Game' to start again!");

}

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