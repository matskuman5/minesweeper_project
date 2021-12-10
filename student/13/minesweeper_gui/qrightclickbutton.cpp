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
