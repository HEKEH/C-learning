#include "Step.h"

Step::Step(int moveid, int killid, int rowFrom, int colFrom, int rowTo, int colTo)
{
    _moveid = moveid;
    _killid = killid;
    _rowFrom = rowFrom;
    _colFrom = colFrom;
    _rowTo = rowTo;
    _colTo = colTo;
}
