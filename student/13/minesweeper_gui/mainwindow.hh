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

    // handles left clicks on the gameboard squares (i.e. attempting to open squares)
    // if the opening is successful, calls open_button_board to handle the opening
    void square_leftclick();

    // handles right clicks on the gameboard squares (i.e. flagging squares)
    void square_rightclick();

    // handles clicks on the 'new game' button (i.e. generates a new board)
    void new_game_button_click();

    // handles clicks on the 'clear' button (i.e. checks if flags have been misplaced)
    void check_button_click() const;

    // triggers once per second to increment the game timer
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

    // initializes a new game board by generating the buttons
    void init_squares();

    // handles the opening of gameboard squares on the internal GameBoard level
    // calls open_button_ui to handle opening the UI buttons corresponding to the squares
    void open_button_board(int x, int y);

    // handles the opening of gameboard squares on the UI level (disabling the button, for example)
    void open_button_ui(int x, int y);

    // handles ending a lost or won game
    void end_game(bool won);

    // returns the coordinates of a gameboard button from its name
    std::vector<int> coordinates_from_string(std::string s) const;

    // returns a pointer to the desired gameboard button from its coordinates
    QToolButton* get_button(int x, int y) const;
};
#endif // MAINWINDOW_HH
