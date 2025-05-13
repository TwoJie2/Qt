#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    // explicit MyPushButton(QPushButton *parent = nullptr);

    MyPushButton(QString Img);
    QString Imgpath;
signals:
};

#endif // MYPUSHBUTTON_H
