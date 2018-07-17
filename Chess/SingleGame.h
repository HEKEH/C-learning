#ifndef SINGLEGAME_H
#define SINGLEGAME_H
#include "Board.h"


class SingleGame : public Board
{
    Q_OBJECT
public:
    explicit SingleGame(QWidget *parent = nullptr);
    int _level;

    void click(int id, int row, int col);

    Step* getBestMove();
    void getAllPossibleMove(std::vector<Step*> &steps);

    void fakeMove(Step* step);
    void unFakeMove(Step* step);
    int getScore();
    int getMinScore(int level, int tempMaxInMinScores);
    int getMaxScore(int level, int tempMInInMaxScores);

//    int getMinScore(int level, int curMin);
//    int getMaxScore(int level, int curMax);
//    int score();

//    void fakeMove(Step* step);
//    void unfakeMove(Step* step);

signals:

public slots:
    void slotBack();
    void computerMove();
};

#endif // SINGLEGAME_H
