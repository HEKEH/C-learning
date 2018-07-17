#ifndef BOARD_H
#define BOARD_H

//#include <iostream>
#include <QWidget>
#include <QMouseEvent>
#include "Stone.h"
#include "Step.h"
#include <vector>

//using namespace std;
class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);

    bool _bRedSide;

    int _r;

    bool _redTurn = true;

    int _selectid = -1;

    Stone _s[32];

    QPoint center(int row, int col);
    QPoint center(int id);
    std::vector<Step*> _steps;

    void init(bool bRedSide);
    void drawStone(QPainter& painter, int id);
    void drawGrid(QPainter& painter);

    virtual void paintEvent(QPaintEvent *);

    virtual void mouseReleaseEvent(QMouseEvent *);

    //int selectStone(int row, int col);

    void click(QPoint pt);
    virtual void click(int id, int row, int col);
    bool getClickRowCol(int &row, int &col, QPoint pt);
    int getStoneId(int row, int col);

    bool canMoveJIANG(int moveid, int row, int col);
    bool canMoveJU(int moveid, int row, int col);
    bool canMovePAO(int moveid, int row, int col, int killid);
    bool canMoveMA(int moveid, int row, int col);
    bool canMoveBING(int moveid, int row, int col);
    bool canMoveSHI(int moveid, int row, int col);
    bool canMoveXIANG(int moveid, int row, int col);
    bool canMove(int moveid, int row, int col, int killid);
    void moveStone(int moveid, int row, int col, int clickid);
    void moveStone(int moveid, int row, int col);

    void relieveStone(int id);
    void saveStep(int moveid, int killid, int rowFrom, int colFrom, int rowTo, int colTo);
    void backOne();

signals:

public slots:
    void slotBack();
};

#endif // BOARD_H
