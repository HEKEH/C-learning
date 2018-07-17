#include "SingleGame.h"
#include <QTimer>

SingleGame::SingleGame(QWidget *parent) : Board(parent)
{
    _level = 3;
}

void SingleGame::slotBack()
{
    if(_redTurn)
    {
        backOne();
        backOne();
    }
}

void SingleGame::click(int id, int row, int col)
{
    if(_redTurn)
    {
        Board::click(id, row, col);
        if(!_redTurn)
        {
            QTimer::singleShot(50, this, SLOT(computerMove()));
        }
    }
}

void SingleGame::computerMove()
{
    Step* step = getBestMove();
    moveStone(step->_moveid, step->_rowTo, step->_colTo, step->_killid);
    delete step;
}

Step* SingleGame::getBestMove()
{
    Step* ret = NULL;
    std::vector<Step*> steps;
    getAllPossibleMove(steps);
    int maxInMinScores = -10000;
    while(steps.size() != 0)
    {
        Step* s = steps.back();
        steps.pop_back();
        fakeMove(s);
        int score = getMinScore(this->_level, maxInMinScores);
        unFakeMove(s);
        if(maxInMinScores < score)
        {
            maxInMinScores = score;
            if(ret)
            {
                delete ret;
            }
            ret = s;
        }
        else
        {
            delete s;
        }
    }
    return ret;
}

void SingleGame::fakeMove(Step* step)
{
    //_s[step->_killid]._type = Stone::JIANG;
    moveStone(step->_moveid, step->_rowTo, step->_colTo);
    if (step->_killid != -1)
        _s[step->_killid]._dead = true;
    _redTurn = !_redTurn;
}

void SingleGame::unFakeMove(Step* step)
{
    moveStone(step->_moveid, step->_rowFrom, step->_colFrom);
    relieveStone(step->_killid);
    _redTurn = !_redTurn;
}

int SingleGame::getScore()
{
    int blackScore = 0;
    int redScore = 0;
    //enum TYPE{JIANG, JU, PAO, MA, BING, SHI, XIANG};
    static int StoneScore[] = {5000, 200, 100, 100, 20, 50, 40};
    for(int i = 0; i < 32; i++)
    {
        if(_s[i]._dead) continue;
        if(_s[i]._red)
        {
            redScore += StoneScore[_s[i]._type];
        } else
        {
            blackScore += StoneScore[_s[i]._type];
        }

    }
    return blackScore - redScore;
}

int SingleGame::getMinScore(int level, int tempMaxInMinScores)
{
    if(level == 0)
    {
        return getScore();
    }
    std::vector<Step*> steps;
    getAllPossibleMove(steps);
    int minInMaxScores = 10000;
    while(steps.size() != 0)
    {
        Step* s = steps.back();
        steps.pop_back();
        fakeMove(s);
        int score = getMaxScore(level - 1,minInMaxScores);
        unFakeMove(s);
        if (score <= tempMaxInMinScores)
            return score;;
        if (minInMaxScores > score)
        {
            minInMaxScores = score;
        }

        delete s;

    }
    return minInMaxScores;
}

int SingleGame::getMaxScore(int level, int tempMInInMaxScores)
{
    if(level == 0)
    {
        return getScore();
    }
    std::vector<Step*> steps;
    getAllPossibleMove(steps);
    int maxInMinScores = -10000;
    while(steps.size() != 0)
    {
        Step* s = steps.back();
        steps.pop_back();
        fakeMove(s);
        int score = getMinScore(level - 1,maxInMinScores);
        unFakeMove(s);
        if (score >= tempMInInMaxScores)
            return score;
        if (maxInMinScores < score)
        {
            maxInMinScores = score;
        }

        delete s;
    }
    return maxInMinScores;

}

void SingleGame::getAllPossibleMove(std::vector<Step*> &steps)
{
    int minI = 16;
    int maxI = 32;
    if(_redTurn)
    {
        minI = 0;
        maxI = 16;
    }
    for(int i = minI; i < maxI; i++)
    {
        if(_s[i]._dead)
        {
            continue;
        }
        int rF = _s[i]._row;
        int cF = _s[i]._col;
        for(int r = 0; r < 10; r++)
        {
            for(int c = 0; c < 9; c++)
            {
                int killid = getStoneId(r, c);
                if(canMove(i, r, c, killid)){
                    Step* s = new Step(i, killid, rF, cF, r, c);
                    steps.push_back(s);
                }
            }
        }
    }
}
