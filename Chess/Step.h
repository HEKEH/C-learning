#ifndef STEP_H
#define STEP_H


class Step
{
public:
    Step(int moveid, int killid, int rowFrom, int colFrom, int rowTo, int colTo);
    int _moveid;
    int _killid;
    int _rowFrom;
    int _colFrom;
    int _rowTo;
    int _colTo;

};

#endif // STEP_H
