// MINESWEEPER GUI PROJECT
// PROGRAMMING 2 COURSE
// Author: Matias Selin
// Student number: 150181798

#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "qrightclickbutton.hh"
#include <QDebug>
#include <string>
#include <QToolButton>
#include <QTimer>
#include <map>

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
    connect(check_button_, &QPushButton::clicked, this, &MainWindow::check_button_click);

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

void MainWindow::init_squares() {

    for (int x = 0; x < board_size_spinbox_->value(); x++) {
        for (int y = 0; y < board_size_spinbox_->value(); y++) {

            // the coordinates of a button are stored in its ObjectName in the form "x y"
            // the coordinates_from_string function can later return these coordinates in a std::vector of ints
            QString button_name = QString::fromStdString(std::to_string(x) + " " + std::to_string(y));

            QRightClickButton* rightclickButton = new QRightClickButton(this);
            rightclickButton->setObjectName(button_name);

            //set the SizePolicy of the button to Expanding so it resizes properly
            QSizePolicy sp = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            rightclickButton->setSizePolicy(sp);

            rightclickButton->setStyleSheet("QToolButton { background-color: rgb(200,200,200)}");

            buttons_.push_back(rightclickButton);

            connect(rightclickButton, &QToolButton::clicked, this, &MainWindow::square_leftclick);
            connect(rightclickButton, &QRightClickButton::rightClicked, this, &MainWindow::square_rightclick);

            board_grid->addWidget(rightclickButton, y, x);

        }
    }

}

void MainWindow::square_leftclick() {

    for (auto b : buttons_) {
        if (b == sender()) {

            qDebug() << "clicked on " << b->objectName();

            std::vector<int> xy = coordinates_from_string(b->objectName().toStdString());
            int x = xy.at(0);
            int y = xy.at(1);

            open_button_board(x, y);

            break;
        }
    }

}

void MainWindow::open_button_board(int x, int y) {

    Square s = board_.getSquare(x, y);

    if (s.hasFlag()) {
        return;
    }

    open_button_ui(x, y);

    if (s.hasMine()) {
        end_game(false);
    } else {
//        qDebug() << "<handle_opening> adjacent mines: " << board_.getSquare(x, y).countAdjacent();

        if (board_.getSquare(x, y).countAdjacent() == 0) {

//            qDebug() << "<handle_opening> opening adjacent squares";
            int min_x = std::max(0, x - 1);
            int max_x = std::min(board_.getSize() - 1, x + 1);
            int min_y = std::max(0, y - 1);
            int max_y = std::min(board_.getSize() - 1, y + 1);

            for(int y_2 = min_y; y_2 <= max_y; ++y_2) {
                for(int x_2 = min_x; x_2 <= max_x; ++x_2) {
//                    qDebug() << "<handle_opening> square: " << x_2 << ", " << y_2 << ", open: " << board_.getSquare(x_2, y_2).isOpen();

                    QToolButton* b = get_button(x_2, y_2);

                    if(b->isEnabled()) {
//                        qDebug() << "<handle_opening> recursive opening";
                        open_button_board(x_2, y_2);
                    }
                }
            }
        }

        qDebug() << "opening BOARD square " << x << ", " << y;
        board_.openSquare(x, y);

        if (board_.isGameOver()) {
            end_game(true);
        }
    }
}

void MainWindow::open_button_ui(int x, int y) {

    QToolButton* b = get_button(x, y);

    Square s = board_.getSquare(x, y);

    if (s.hasMine()) {
        b->setIcon(QPixmap(":/images/bomb.png"));
    } else {

        const std::vector<std::string> number_colors = {"blue", "green", "red", "purple",
                                                        "brown", "teal", "black", "gray"};

        int mines = s.countAdjacent();

        if (mines != 0) {
            b->setText(QString::number(mines));
            QString stylesheet = QString::fromStdString("QToolButton { color: " + number_colors.at(mines - 1) + "; font: bold; background-color: rgb(230, 230, 230) }");
            b->setStyleSheet(stylesheet);
        } else {
            b->setStyleSheet("QToolButton { background-color: rgb(230,230,230)}");
        }
        qDebug() << "<open_square_button> disabling " << x << ", " << y;
        b->setDisabled(true);
    }

}

void MainWindow::square_rightclick() {

    for (auto b : buttons_) {
        if (b == sender()) {

            std::string coordinates = b->objectName().toStdString();

            std::vector<int> xy = coordinates_from_string(coordinates);
            int x = xy.at(0);
            int y = xy.at(1);

            qDebug() << b->objectName();
            qDebug() << b->objectName().indexOf("q");

            // a square marked with a question mark has a 'q' at the end of its ObjectName
            // a bit hacky, but it works
            if (b->objectName().indexOf("q") != -1) {
                QString new_name = b->objectName();
                new_name.chop(2);
                b->setObjectName(new_name);

                //remove the question mark by setting the icon to be an empty image
                b->setIcon(QIcon());
                return;
            }

            if (board_.flagSquare(x, y)) {
                qDebug() << "flagged " << x << ", " << y;

                b->setIcon(QPixmap(":/images/flag.png"));

            } else {
                qDebug() << "deflagged " << x << ", " << y;

                // right-clicking an already flagged square turns the flag into a question mark
                b->setIcon(QPixmap(":/images/question_mark.png"));

                // add a 'q' to the ObjectName so we know that the square is marked with a question mark
                b->setObjectName(b->objectName() + " q");
            }

            if (board_.isGameOver()) {
                end_game(true);
            }

            break;

        }
    }

}

void MainWindow::end_game(bool won) {

    for (auto b : buttons_) {
        b->setDisabled(true);
    }

    timer_->stop();

    if (won) {
        text_browser_->append("You won, great job!");
    } else {
        text_browser_->append("BOOM! You lost!");
    }

    text_browser_->append("Game over! Enter a seed and press 'New Game' to start again!");

}

void MainWindow::new_game_button_click() {

    QString seed = seed_line_edit_->text();

    for (auto qc : seed) {
        if (!qc.isDigit()) {
            text_browser_->append("Error: seed must be an integer value");
            return;
        }
    }

    if (seed.isEmpty()) {
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

    board_.init(seed.toInt(), board_size_spinbox_->value());

    init_squares();

    minutes_ = 0;
    seconds_ = 0;
    timer_->start();

}

void MainWindow::check_button_click() const {

    int misplaced_flags = 0;

    for(int y = 0; y < board_.getSize(); ++y) {
        for(int x = 0; x < board_.getSize(); ++x) {

            Square s = board_.getSquare(x, y);
            if (s.hasFlag() && !s.hasMine()) {
                misplaced_flags++;
            }

        }
    }

    if (misplaced_flags > 0) {
        QString message = QString::fromStdString("Oops! You've placed " + std::to_string(misplaced_flags) + " flag(s) in the wrong square(s)!");
        text_browser_->append(message);
    } else {
        text_browser_->append("No misplaced flags so far, nice!");
    }

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

std::vector<int> MainWindow::coordinates_from_string(std::string s) const {

    std::vector<int> coordinates;

    int x = std::stoi(s.substr(0, s.find(" ")));
    s.erase(0, s.find(" ") + 1);
    int y = std::stoi(s);

    coordinates.push_back(x);
    coordinates.push_back(y);

    return coordinates;

}

QToolButton *MainWindow::get_button(int x, int y) const {

    for (auto b : buttons_) {
        std::string coordinates = b->objectName().toStdString();

        std::vector<int> xy = coordinates_from_string(coordinates);
        int x_b = xy.at(0);
        int y_b = xy.at(1);

        if (x == x_b && y == y_b) {
            return b;
        }

    }

    return nullptr;

}
