#include "Board.h"
#include <QPainter>
//#include <iostream>
//#include <stdio.h>

#define max(a,b)(a>b?a:b)
#define min(a,b)(a<b?a:b)
#define GetRowCol(__row, __col, __id)\
    int __row = _s[__id]._row;\
    int __col = _s[__id]._col;


Board::Board(QWidget *parent) : QWidget(parent)
{
    _r = 20;
    setMinimumSize(_r*18+1, _r*20+1);
    init(true);
}

void Board::init(bool isPlayerRedSide)
{
    _bRedSide = isPlayerRedSide;
    for(int i = 0; i < 32; i++)
    {
        _s[i].init(i);
    }
    if(isPlayerRedSide)
    {
        for(int i = 0; i < 32; i++)
        {
            _s[i].rotate();
        }
    }
}

void Board::paintEvent(QPaintEvent *)
{
    //std::cout << _steps[0]->_colFrom << std::endl;
    _r = height()/22;
    QPainter painter(this);
    //绘制棋盘
    drawGrid(painter);

    //绘制32颗棋子
    for(int i = 0; i < 32; i++)
    {
        drawStone(painter, i);
    }
}

void Board::mouseReleaseEvent(QMouseEvent *ev)
{
    QPoint pt = ev->pos();
    click(pt);
}

void Board::click(QPoint pt)
{
    int row, col;
    bool inBoard = getClickRowCol(row, col, pt);
    if(!inBoard) return;

    int id = getStoneId(row, col);
    click(id, row, col);
}

void Board::click(int id, int row, int col)
{
    if (_selectid == -1)//选中棋子
    {
        if(id != -1 && _s[id]._red == _redTurn)
        {
            _selectid = id;
        }
    }
    else//移动选中棋子
    {
        int clickid = id;
        //_s[0]._type = _s[-1]._type;
        if (canMove(_selectid, row, col, clickid)) {
            moveStone(_selectid, row, col, clickid);
        }
    }
    update();
}

bool Board::getClickRowCol(int &row, int &col, QPoint pt)
{
    row = (pt.y() + _r) / (_r * 2) - 1;//+ _r是为了四舍五入
    col = (pt.x() + _r) / (_r * 2) - 1;
    if(row > - 1 && row < 10 && col > -1 && col < 9)
        return true;
    return false;
}

int Board::getStoneId(int row, int col)
{
    int id = -1;
    for(int i = 0; i < 32; i++)
    {
        if (_s[i]._row == row && _s[i]._col == col && !_s[i]._dead)
        {
            id = i;
            break;
        }
    }
    return id;
}

void Board::moveStone(int moveid, int row, int col, int clickid)
{
    GetRowCol(rowF, colF, moveid)
    saveStep(moveid, clickid, rowF, colF, row, col);

    moveStone(moveid, row, col);
    if (clickid != -1)
        _s[clickid]._dead = true;
        clickid = -1;
    this->_selectid = -1;
    _redTurn = !_redTurn;
}


void Board::moveStone(int moveid, int row, int col)
{
    //_s[moveid]._type = Stone::BING;
    _s[moveid]._row = row;
    _s[moveid]._col = col;
}


bool Board::canMove(int moveid, int row, int col, int killid)
{
    if (killid == moveid)
        return false;
    if (killid != -1 && _s[moveid]._red == _s[killid]._red){
        _selectid = killid;
        update();
        return false;
    }

    switch (_s[moveid]._type) {
    case Stone::JIANG:
        return canMoveJIANG(moveid, row, col);

    case Stone::JU:
        return canMoveJU(moveid, row, col);

    case Stone::PAO:
        return canMovePAO(moveid, row, col, killid);

    case Stone::MA:
        return canMoveMA(moveid, row, col);

    case Stone::BING:
        return canMoveBING(moveid, row, col);

    case Stone::SHI:
        return canMoveSHI(moveid, row, col);

    case Stone::XIANG:
        return canMoveXIANG(moveid, row, col);
    }
    return false;
}

bool Board::canMoveJIANG(int moveid, int row, int col)
{
    if (col < 3 || col > 5)
        return false;

    if(_s[moveid]._bUpside)
    {
        if (row > 3)
            return false;
    } else
    {
        if (row < 7)
            return false;
    }

    int d = abs(_s[moveid]._row - row) + abs(_s[moveid]._col - col);

    if(d != 1)
        return false;

    return true;
}


bool Board::canMoveJU(int moveid, int row, int col)
{
    if(_s[moveid]._row == row)
    {
        int cmin = min(_s[moveid]._col, col);
        int cmax = max(_s[moveid]._col, col);
        for (int j = 0; j < 32; j++)
        {
            if (_s[j]._row == row && _s[j]._col > cmin && _s[j]._col < cmax && _s[j]._dead == false)
                return false;
        }
        return true;
    }
    else if(_s[moveid]._col == col)
    {
        int rmin = min(_s[moveid]._row, row);
        int rmax = max(_s[moveid]._row, row);

        for (int j = 0; j < 32; j++)
        {
            if (_s[j]._col == col && _s[j]._row > rmin && _s[j]._row < rmax && _s[j]._dead == false)
                return false;
        }
        return true;
    }
    return false;
}
bool Board::canMovePAO(int moveid, int row, int col, int killid)
{
    if(killid == -1)
    {
        if(_s[moveid]._row == row)
        {
            int cmin = min(_s[moveid]._col, col);
            int cmax = max(_s[moveid]._col, col);
            for (int j = 0; j < 32; j++)
            {
                if (_s[j]._row == row && _s[j]._col > cmin && _s[j]._col < cmax && _s[j]._dead == false)
                    return false;
            }
            return true;
        }
        else if(_s[moveid]._col == col)
        {
            int rmin = min(_s[moveid]._row, row);
            int rmax = max(_s[moveid]._row, row);

            for (int j = 0; j < 32; j++)
            {
                if (_s[j]._col == col && _s[j]._row > rmin && _s[j]._row < rmax && _s[j]._dead == false)
                    return false;
            }
            return true;
        }
        return false;
    }
    else
    {
        int count = 0;
        if(_s[moveid]._row == row)
        {
            int cmin = min(_s[moveid]._col, col);
            int cmax = max(_s[moveid]._col, col);
            for (int j = 0; j < 32; j++)
            {
                if (_s[j]._row == row && _s[j]._col > cmin && _s[j]._col < cmax && _s[j]._dead == false)
                    count++;
            }
            if(count == 1)
                return true;
            else
                return false;
        }
        else if(_s[moveid]._col == col)
        {
            int rmin = min(_s[moveid]._row, row);
            int rmax = max(_s[moveid]._row, row);

            for (int j = 0; j < 32; j++)
            {
                if (_s[j]._col == col && _s[j]._row > rmin && _s[j]._row < rmax && _s[j]._dead == false)
                    count++;
            }
            if(count == 1)
                return true;
            else
                return false;
        }
        return false;
    }

}
bool Board::canMoveMA(int moveid, int row, int col)
{
    int dcol =col - _s[moveid]._col;
    int drow = row - _s[moveid]._row;
    if (abs(dcol) == 2 && abs(drow) == 1)
    {
        for (int j = 0; j < 32; j++)
        {
            if (_s[j]._row == _s[moveid]._row && (_s[j]._col - _s[moveid]._col) == (dcol / 2) && _s[j]._dead == false)
               return false;
        }
        return true;
    }
    else if (abs(dcol) == 1 && abs(drow) == 2)
    {
        for (int j = 0; j < 32; j++)
        {
            if (_s[j]._col == _s[moveid]._col && (_s[j]._row - _s[moveid]._row) == (drow / 2) && _s[j]._dead == false)
               return false;
        }
        return true;
    }
    return false;

}
bool Board::canMoveBING(int moveid, int row, int col)
{

    if (_s[moveid]._bUpside)
    {
        if (_s[moveid]._col == col && (row - _s[moveid]._row) == 1)
            return true;
        else if (_s[moveid]._row == row && abs(col - _s[moveid]._col) == 1 && _s[moveid]._row > 4)
            return true;
    }
    else
    {
        if (_s[moveid]._col == col && (row - _s[moveid]._row) == -1)
            return true;
        else if (_s[moveid]._row == row && abs(col - _s[moveid]._col) == 1 && _s[moveid]._row < 5)
            return true;
    }
    return false;
}

bool Board::canMoveSHI(int moveid, int row, int col)
{
    if (col < 3 || col > 5)
        return false;

    if (_s[moveid]._bUpside)
    {
        if (row > 3)
            return false;
    } else
    {
        if (row < 7)
            return false;
    }

    int d1 = abs(_s[moveid]._row - row);
    int d2 = abs(_s[moveid]._col - col);

    if(d1 != 1 || d2 != 1)
        return false;

    return true;
}
bool Board::canMoveXIANG(int moveid, int row, int col)
{
    if(col != 0 && col != 2 && col != 4 && col != 6 && col != 8)
        return false;
    if(_s[moveid]._bUpside)
    {
        if(row != 0 && row != 2 && row != 4)
            return false;
    }
    else
    {
        if(row != 9 && row != 7 && row != 5)
            return false;
    }
    int dcol =col - _s[moveid]._col;
    int drow = row - _s[moveid]._row;
    if (abs(dcol) == 2 && abs(drow) == 2)
    {
        for (int j = 0; j < 32; j++)
        {
            if ((_s[j]._row - _s[moveid]._row) == (drow / 2) && (_s[j]._col - _s[moveid]._col) == (dcol / 2) && _s[j]._dead == false)
               return false;
        }
        return true;
    }
    return false;
}


void Board::relieveStone(int id)
{
    if(id == -1) return;
    _s[id]._dead = false;
}

void Board::saveStep(int moveid, int killid, int rowFrom, int colFrom, int rowTo, int colTo)
{
    Step* step = new Step(moveid, killid, rowFrom, colFrom, rowTo, colTo);
    _steps.push_back(step);
}

void Board::backOne()
{
    if ( _steps.size() != 0)
    {
        Step* step = _steps.back();
        //_s[step->_moveid]._type = Stone::BING;
        relieveStone(step->_killid);
        moveStone(step->_moveid, step->_rowFrom, step->_colFrom);
        _redTurn = _s[step->_moveid]._red;
        delete step;
        _steps.pop_back();
        update();
    }
}

void Board::slotBack()
{
    //_s[1]._type = Stone::BING;
    backOne();
}


QPoint Board::center(int row, int col)
{
    return QPoint(2 * _r * (col + 1), 2 * _r * (row + 1));
}

QPoint Board::center(int id)
{
    return QPoint(2 * _r * (_s[id]._col + 1), 2 * _r * (_s[id]._row + 1));

}

void Board::drawStone(QPainter &painter, int id)
{
    QPen pen = painter.pen();
    if(_s[id]._dead)
        return;
    QPoint c = center(id);
    QRect rect = QRect(c.x() - _r, c.y() - _r, 2 * _r, 2 * _r);
    if(_selectid == id)
        painter.setBrush(Qt::gray);
    else
        painter.setBrush(Qt::yellow);
    pen.setColor(Qt::black);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawEllipse(c, _r, _r);
    if (_s[id]._red)
        pen.setColor(Qt::red);
        painter.setPen(pen);
    painter.setFont(QFont("楷体", _r, 700));
    painter.drawText(rect, _s[id].getText(), QTextOption(Qt::AlignCenter));
}

void Board::drawGrid(QPainter &painter)
{
    QPen pen = painter.pen();

    //画10条横线
    for(int i = 1; i < 11; i++)
    {
        if (i == 1 || i == 10)
        {
            pen.setWidth(3);
        }
        else{
            pen.setWidth(1);
        }
        painter.setPen(pen);
        painter.drawLine(QPoint(2 * _r, i * 2 * _r), QPoint(9 * 2 * _r, i * 2 * _r));
    }
    //画9条竖线
    for(int i = 1; i < 10; i++)
    {
        if (i == 1 || i == 9)
        {
            pen.setWidth(3);
            painter.setPen(pen);
            painter.drawLine(QPoint(i * 2 * _r, 2 * _r), QPoint(i * 2 * _r, 10 * 2 * _r));
        }
        else
        {
            pen.setWidth(1);
            painter.setPen(pen);
            painter.drawLine(QPoint(i * 2 * _r, 2 * _r), QPoint(i * 2 * _r, 5 * 2 * _r));
            painter.drawLine(QPoint(i * 2 * _r, 6 * 2 * _r), QPoint(i * 2 * _r, 10 * 2 * _r));
        }
    }
    //画9宫格
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawLine(QPoint(4 * 2 * _r, 2 * _r), QPoint(6 * 2 * _r, 3 * 2 * _r));
    painter.drawLine(QPoint(6 * 2 * _r, 2 * _r), QPoint(4 * 2 * _r, 3 * 2 * _r));

    painter.drawLine(QPoint(4 * 2 * _r, 10 * 2 * _r), QPoint(6 * 2 * _r, 8 * 2 * _r));
    painter.drawLine(QPoint(6 * 2 * _r, 10 * 2 * _r), QPoint(4 * 2 * _r, 8 * 2 * _r));
}

