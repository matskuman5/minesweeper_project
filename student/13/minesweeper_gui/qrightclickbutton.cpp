// MINESWEEPER GUI PROJECT
// PROGRAMMING 2 COURSE
// Author: Matias Selin
// Student number: 150181798

#include "qrightclickbutton.hh"

QRightClickButton::QRightClickButton(QWidget *parent) :
    QToolButton(parent) {
}

void QRightClickButton::mousePressEvent(QMouseEvent *e) {

    if(e->button()==Qt::RightButton) {
        emit rightClicked();
    }

    QToolButton::mousePressEvent(e);
}
