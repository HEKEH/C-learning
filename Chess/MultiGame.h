#ifndef MULTIGAME_H
#define MULTIGAME_H
#include "Board.h"


class MultiGame : public Board
{
    Q_OBJECT
public:
    explicit MultiGame(QWidget *parent = nullptr);
};

#endif // MULTIGAME_H
