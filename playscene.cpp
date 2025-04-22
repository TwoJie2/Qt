#include "playscene.h"
#include <QPainter>
#include "mypushbutton.h"
#include <mycoin.h>
#include <QDebug>
#include <QtGlobal>
#include <QSpinBox>

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

    num=5;
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            int now=0;
            if ((i==3 && j==3) || (i==4 && j==4)) now=2;
            if ((i==3 && j==4) || (i==4 && j==3)) now=1;
            if ((i==2 && j==3) || (i==3 && j==2) || (i==4 && j==5) || (i==5 && j==4)) now=3;
            Mycoin * coin = new Mycoin(now,i,j);
            coin->setParent(this);
            coin->move(50+i*88,54+j*88);

            connect(coin,&Mycoin::clicked,[=](){
                if (coin->flag==3){
                    coin->set(2-num%2);
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
                    int col=2-num%2;
                    for (int k=0;k<8;k++)
                        for (int l=0;l<8;l++){
                            if (a[k][l]->flag==1 || a[k][l]->flag==2) continue;
                            if (check(k,l,col)) a[k][l]->set(3);
                            else a[k][l]->set(0);
                        }
                    ////////////////////////////////////////////////
                    int res=0,res2=0;
                    for (int k=0;k<8;k++)
                        for (int l=0;l<8;l++){
                            if (a[k][l]->flag==1) res++;
                            if (a[k][l]->flag==2) res2++;
                        }
                    cnt->setValue(res);
                    cnt2->setValue(res2);
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
}
void Playscene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/background.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
