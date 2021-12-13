#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QToolButton>
#include <QGridLayout>
#include <QPushButton>
#include <QTextBrowser>
#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>
#include <gameboard.hh>
#include <vector>
#include "qrightclickbutton.hh"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void square_leftclick();
    void square_rightclick();
    void new_game_button_click();
    void check_button_click() const;
    void timer_tick();

private:
    Ui::MainWindow *ui;

    GameBoard board_;

    std::vector<QRightClickButton*> buttons_;
    QWidget* central;
    QGridLayout* main_grid;
    QGridLayout* board_grid;
    QGridLayout* button_grid;

    QPushButton* new_game_button_;
    QPushButton* check_button_;
    QLineEdit* seed_line_edit_;
    QSpinBox* board_size_spinbox_;
    QLabel* board_size_label_;

    QTextBrowser* text_browser_;
    QTimer* timer_;
    QLabel* time_;

    unsigned int minutes_;
    unsigned int seconds_;

    void open_button(int x, int y);
    void init_squares();
    void end_game(bool won);
    std::vector<int> coordinates_from_string(std::string s) const;
    void handle_opening(int x, int y);
    QToolButton* get_button(int x, int y) const;
};
#endif // MAINWINDOW_HH
