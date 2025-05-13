#include "playscene.h"
#include <QPainter>
#include "mypushbutton.h"
#include <mycoin.h>
#include <QDebug>
#include <QtGlobal>
#include <QSpinBox>
#include <QPropertyAnimation>

Playscene::Playscene(QWidget *parent)
    : QWidget{parent}
{
    QPixmap pix;
    pix.load(":/res/background.jpg");
    setFixedSize(pix.width(),pix.height());
    setWindowTitle("黑白棋对战界面");
    setWindowIcon(QIcon(":/res/background.jpg"));

    MyPushButton * backbtn = new MyPushButton(":/res/back.jpg");
    backbtn->setParent(this);
    backbtn->move(this->width() - backbtn->width(),this->height() - backbtn->height());

    connect(backbtn,&MyPushButton::clicked,[=](){
        emit this->backsignal();
    });

    MyPushButton * bcountbtn = new MyPushButton(":/res/bcount.jpg");
    bcountbtn->setParent(this);
    bcountbtn->move(850,300);

    MyPushButton * wcountbtn = new MyPushButton(":/res/wcount.jpg");
    wcountbtn->setParent(this);
    wcountbtn->move(850,380);

    MyPushButton * pointer = new MyPushButton(":/res/pointer.png");
    pointer->setParent(this);
    pointer->move(805,325);

    QSpinBox * cnt = new QSpinBox(this);
    cnt->setValue(2);
    cnt->move(960,315);
    cnt->setFixedSize(80,50);
    cnt->setButtonSymbols(QAbstractSpinBox::NoButtons);
    cnt->setReadOnly(true);
    cnt->setFocusPolicy(Qt::NoFocus);
    cnt->setStyleSheet(
        "QSpinBox {"
        "   background: transparent;"  // 背景透明
        "   border: none;"            // 移除边框（可选）
        "   color: black;"               // 文字颜色
        "   font-size: 30px;"          // 字号
        "}"
        );

    QSpinBox * cnt2 = new QSpinBox(this);
    cnt2->setValue(2);
    cnt2->move(960,395);
    cnt2->setFixedSize(80,50);
    cnt2->setButtonSymbols(QAbstractSpinBox::NoButtons);
    cnt2->setReadOnly(true);
    cnt2->setFocusPolicy(Qt::NoFocus);
    cnt2->setStyleSheet(
        "QSpinBox {"
        "   background: transparent;"  // 背景透明
        "   border: none;"            // 移除边框（可选）
        "   color: white;"               // 文字颜色
        "   font-size: 30px;"          // 字号
        "}"
    );

    MyPushButton * bwin = new MyPushButton(":/res/bwin.png");
    bwin->setParent(this);
    bwin->move(this->width(),150);

    QPropertyAnimation * banimation = new QPropertyAnimation(bwin,"geometry");
    banimation->setDuration(1000);
    banimation->setStartValue(QRect(bwin->x(),bwin->y(),bwin->width(),bwin->height()));
    banimation->setEndValue(QRect(bwin->x()-210,bwin->y(),bwin->width(),bwin->height()));
    banimation->setEasingCurve(QEasingCurve::Linear);

    MyPushButton * wwin = new MyPushButton(":/res/wwin.png");
    wwin->setParent(this);
    wwin->move(this->width(),150);

    QPropertyAnimation * wanimation = new QPropertyAnimation(wwin,"geometry");
    wanimation->setDuration(1000);
    wanimation->setStartValue(QRect(wwin->x(),wwin->y(),wwin->width(),wwin->height()));
    wanimation->setEndValue(QRect(wwin->x()-210,wwin->y(),wwin->width(),wwin->height()));
    wanimation->setEasingCurve(QEasingCurve::Linear);

    MyPushButton * pwin = new MyPushButton(":/res/pwin.png");
    pwin->setParent(this);
    pwin->move(this->width(),150);

    QPropertyAnimation * panimation = new QPropertyAnimation(pwin,"geometry");
    panimation->setDuration(1000);
    panimation->setStartValue(QRect(pwin->x(),pwin->y(),pwin->width(),pwin->height()));
    panimation->setEndValue(QRect(pwin->x()-210,pwin->y(),pwin->width(),pwin->height()));
    panimation->setEasingCurve(QEasingCurve::Linear);

    num=5;nowflag=1;
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            int now=0;
            if ((i==3 && j==3) || (i==4 && j==4)) now=2;
            if ((i==3 && j==4) || (i==4 && j==3)) now=1;
            if ((i==2 && j==3) || (i==3 && j==2) || (i==4 && j==5) || (i==5 && j==4)) now=3;
            Mycoin * coin = new Mycoin(now,i,j);
            coin->setParent(this);
            coin->move(50+i*88,54+j*88);

            connect(coin,&Mycoin::clicked,this,[=](){
                if (coin->flag==3){
                    coin->set(nowflag);
                    ////////////////////////////////////////////////
                    for (int i=0;i<8;i++){
                        int line=8;
                        if (mov[i][0]==-1) line=coin->x;
                        if (mov[i][0]==1) line=7-coin->x;
                        if (mov[i][1]==-1) line=qMin(line,coin->y);
                        if (mov[i][1]==1) line=qMin(line,7-coin->y);
                        int step=0;
                        for (int k=1;k<=line;k++){
                            if (a[coin->x+k*mov[i][0]][coin->y+k*mov[i][1]]->flag!=3-coin->flag){
                                step=k;
                                break;
                            }
                        }
                        if (step<=line && a[coin->x+step*mov[i][0]][coin->y+step*mov[i][1]]->flag==coin->flag)
                            for (int k=1;k<step;k++) a[coin->x+k*mov[i][0]][coin->y+k*mov[i][1]]->set(coin->flag);
                    }
                    ///////////////////////////////////////////////////////////////
                    this->add();
                    pointer->move(805,730-pointer->y());
                    bool can=0;
                    for (int k=0;k<8;k++)
                        for (int l=0;l<8;l++){
                            if (a[k][l]->flag==1 || a[k][l]->flag==2) continue;
                            if (check(k,l,nowflag)) a[k][l]->set(3),can=1;
                            else a[k][l]->set(0);
                        }
                    if (!can){
                        nowflag=3-nowflag;
                        pointer->move(805,730-pointer->y());
                        for (int k=0;k<8;k++)
                            for (int l=0;l<8;l++){
                                if (a[k][l]->flag==1 || a[k][l]->flag==2) continue;
                                if (check(k,l,nowflag)) a[k][l]->set(3),can=1;
                                else a[k][l]->set(0);
                            }
                    }
                    ////////////////////////////////////////////////
                    int res=0,res2=0;
                    bool final=1;
                    for (int k=0;k<8;k++)
                        for (int l=0;l<8;l++){
                            if (a[k][l]->flag==1) res++;
                            if (a[k][l]->flag==2) res2++;
                            if (a[k][l]->flag==3) final=0;
                        }
                    cnt->setValue(res);
                    cnt2->setValue(res2);
                    /////////////////////////////////////////////////
                    if (final){
                        pointer->hide();
                        if (res>res2) banimation->start();
                        if (res<res2) wanimation->start();
                        if (res==res2) panimation->start();
                    }
                }
            });

            a[i][j]=coin;
        }
    }
}

bool Playscene::check(int x,int y,int col){
    Mycoin * coin=a[x][y];
    for (int i=0;i<8;i++){
        int line=8;
        if (mov[i][0]==-1) line=coin->x;
        if (mov[i][0]==1) line=7-coin->x;
        if (mov[i][1]==-1) line=qMin(line,coin->y);
        if (mov[i][1]==1) line=qMin(line,7-coin->y);
        int step=0;
        for (int k=1;k<=line;k++){
            if (a[coin->x+k*mov[i][0]][coin->y+k*mov[i][1]]->flag!=3-col){
                step=k;
                break;
            }
        }
        if (1<step && step<=line && a[coin->x+step*mov[i][0]][coin->y+step*mov[i][1]]->flag==col)
            return 1;
    }
    return 0;
}
void Playscene::add(){
    num++;
    nowflag=3-nowflag;
}
void Playscene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/background.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
