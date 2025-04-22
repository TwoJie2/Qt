#include "mainscene.h"
#include "ui_mainscene.h"
#include "mypushbutton.h"
#include "playscene.h"
#include <QPushButton>
#include <QPainter>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    QPixmap pix;
    pix.load(":/res/background.jpg");
    setFixedSize(pix.width(),pix.height());
    // setFixedSize(1050,800);
    setWindowTitle("黑白棋主界面");
    setWindowIcon(QIcon(":/res/background.jpg"));

    MyPushButton * stbtn = new MyPushButton(":/res/start.jpg");
    stbtn->setParent(this);
    stbtn->move(this->width()*0.99-stbtn->width()*0.99,this->height()*0.5-stbtn->height()*0.5);

    connect(stbtn,&MyPushButton::clicked,this,[=](){
        this->hide();
        playscene = new Playscene;
        playscene->show();
        connect(playscene,&playscene->backsignal,[=](){
            this->show();
            playscene->close();
        });
    });
}

void MainScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/background.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

MainScene::~MainScene()
{
    delete ui;
}
