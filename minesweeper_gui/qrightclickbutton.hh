// MINESWEEPER GUI PROJECT
// PROGRAMMING 2 COURSE
// Author: Matias Selin
// Student number: 150181798

#ifndef QRIGHTCLICKBUTTON_HH
#define QRIGHTCLICKBUTTON_HH

#include <QToolButton>
#include <QMouseEvent>

class QRightClickButton : public QToolButton
{
    Q_OBJECT

public:
    explicit QRightClickButton(QWidget *parent = 0);

private slots:
    void mousePressEvent(QMouseEvent *e);

signals:
    void rightClicked();

public slots:

};



#endif // QRIGHTCLICKBUTTON_HH
