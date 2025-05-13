#include "mypushbutton.h"

MyPushButton::MyPushButton(QString Img){
    this->Imgpath=Img;
    QPixmap pix;
    pix.load(Img);

    this->setFixedSize(pix.width(),pix.height());
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
}
