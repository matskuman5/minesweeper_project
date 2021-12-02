#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QToolButton>
#include <QGridLayout>
#include <gameboard.hh>
#include <vector>

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
    void square_click();

private:
    Ui::MainWindow *ui;

    GameBoard board_;
    unsigned int board_size_;

    std::vector<QToolButton*> buttons_;
    QWidget* central;
    QGridLayout* gLayout;

    void init_squares();

};
#endif // MAINWINDOW_HH
