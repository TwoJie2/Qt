#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QWidget>
#include <mycoin.h>
class Playscene : public QWidget
{
    Q_OBJECT
public:
    explicit Playscene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    int num;
    void add();
    Mycoin * a[8][8];
    const int mov[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    bool check(int x,int y,int col);
signals:
    void backsignal();
};

#endif // PLAYSCENE_H
