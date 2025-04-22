#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>

class Mycoin : public QPushButton
{
    Q_OBJECT
public:
    // explicit Mycoin(QPushButton *parent = nullptr);

    Mycoin(int tmp,int a,int b);

    int flag,x,y;

    void set(int x);
signals:
};

#endif // MYCOIN_H
