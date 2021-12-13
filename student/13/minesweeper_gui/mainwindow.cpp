#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "qrightclickbutton.hh"
#include <QDebug>
#include <string>
#include <QToolButton>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

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
    board_size_spinbox_->setMaximum(30);
    board_size_label_ = new QLabel();
    board_size_label_->setText("Board size: (2-30)");

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

void MainWindow::open_square_button(int x, int y) {

    QToolButton* b = get_button(x, y);

    Square s = board_.getSquare(x, y);

    if (s.hasMine()) {
        std::string filename = ":/images/bomb.png";
        QPixmap image(QString::fromStdString(filename));

        b->setIcon(image);
    } else {
        b->setText(QString::number(s.countAdjacent()));
        qDebug() << "<open_square_button> disabling " << x << ", " << y;
        b->setDisabled(true);
    }

    return;

}

void MainWindow::handle_opening(int x, int y) {

    Square s = board_.getSquare(x, y);

    if (s.hasFlag()) {
        return;
    }

    open_square_button(x, y);

    if (s.hasMine()) {
        end_game(false);
    } else {
        qDebug() << "<handle_opening> adjacent mines: " << board_.getSquare(x, y).countAdjacent();

        if (board_.getSquare(x, y).countAdjacent() == 0) {

            qDebug() << "<handle_opening> opening adjacent squares";

            int min_x = std::max(0, x - 1);
            int max_x = std::min(board_.getSize() - 1, x + 1);
            int min_y = std::max(0, y - 1);
            int max_y = std::min(board_.getSize() - 1, y + 1);

            for(int y_2 = min_y; y_2 <= max_y; ++y_2) {
                for(int x_2 = min_x; x_2 <= max_x; ++x_2) {
                    qDebug() << "<handle_opening> square: " << x_2 << ", " << y_2 << ", open: " << board_.getSquare(x_2, y_2).isOpen();

                    QToolButton* b = get_button(x_2, y_2);

                    if(b->isEnabled()) {
                        qDebug() << "<handle_opening> recursive opening";
                        handle_opening(x_2, y_2);
                    }
                }
            }
        }

        board_.openSquare(x, y);

        if (board_.isGameOver()) {
            end_game(true);
        }
    }

}

void MainWindow::square_leftclick() {

    for (auto b : buttons_) {
        if (b == sender()) {

            qDebug() << "clicked on " << b->objectName();

            std::string coordinates = b->objectName().toStdString();

            std::vector<int> xy = coordinates_from_string(coordinates);
            int x = xy.at(0);
            int y = xy.at(1);

            handle_opening(x, y);

            break;
        }
    }

}

void MainWindow::square_rightclick() {

    for (auto b : buttons_) {
        if (b == sender()) {

            std::string coordinates = b->objectName().toStdString();

            std::vector<int> xy = coordinates_from_string(coordinates);
            int x = xy.at(0);
            int y = xy.at(1);

            if (board_.flagSquare(x, y)) {
                qDebug() << "flagged " << x << ", " << y;

                std::string filename = ":/images/flag.png";
                QPixmap image(QString::fromStdString(filename));

                b->setIcon(image);

            } else {
                qDebug() << "deflagged " << x << ", " << y;

                //remove the flag by setting the icon to be an empty image
                b->setIcon(QIcon());
            }

            break;

        }
    }

}

std::vector<int> MainWindow::coordinates_from_string(std::string s) {

    std::vector<int> coordinates;

    int x = std::stoi(s.substr(0, s.find(" ")));
    s.erase(0, s.find(" ") + 1);
    int y = std::stoi(s);

    coordinates.push_back(x);
    coordinates.push_back(y);

    return coordinates;

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

    board_ = GameBoard();

    board_.init(seed_line_edit_->text().toInt(), board_size_spinbox_->value());

    init_squares();

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

    for (auto b : buttons_) {
        b->setDisabled(true);
    }

    timer_->stop();

    if (won) {
        text_browser_->append("You won, great job!");
        for (auto b : buttons_) {
            if (b->isEnabled()) {
                b->setText("*");
            }
        }
    } else {
        text_browser_->append("BOOM! You lost!");
    }

    text_browser_->append("Game over! Enter a seed and press 'New Game' to start again!");

}

void MainWindow::init_squares() {

    for (unsigned int x = 0; x < board_size_spinbox_->value(); x++) {
        for (unsigned int y = 0; y < board_size_spinbox_->value(); y++) {

            QString button_name = QString::fromStdString(std::to_string(x) + " " + std::to_string(y));

            QRightClickButton* rightclickButton = new QRightClickButton(this);
            rightclickButton->setObjectName(button_name);

            //set the SizePolicy of the button to Expanding so it resizes properly
            QSizePolicy* sp = new QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            rightclickButton->setSizePolicy(*sp);

            buttons_.push_back(rightclickButton);

            connect(rightclickButton, &QToolButton::clicked, this, &MainWindow::square_leftclick);
            connect(rightclickButton, &QRightClickButton::rightClicked, this, &MainWindow::square_rightclick);

            board_grid->addWidget(rightclickButton, y, x);

        }
    }

}

QToolButton *MainWindow::get_button(int x, int y) {

    for (auto b : buttons_) {
        std::string coordinates = b->objectName().toStdString();

        std::vector<int> xy = coordinates_from_string(coordinates);
        int x_2 = xy.at(0);
        int y_2 = xy.at(1);

        if (x == x_2 && y == y_2) {
            return b;
        }

    }

    return nullptr;

}
