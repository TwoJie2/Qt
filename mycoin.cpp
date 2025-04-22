#include "mycoin.h"

Mycoin::Mycoin(int tmp,int a,int b){
    x=a;y=b;
    flag=tmp;
    QPixmap pix;
    QString str=QString(":/res/coin%1.png").arg(tmp);
    pix.load(str);
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
}

void Mycoin::set(int x){
    flag=x;
    QPixmap pix;
    QString str=QString(":/res/coin%1.png").arg(x);
    pix.load(str);
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
}
// Mycoin::Mycoin(QPushButton *parent)
//     : QPushButton{parent}
// {}
