#include "Stone.h"

using namespace std;
Stone::Stone()
{

}

void Stone::init(int id)
{
    _id = id;
    _dead = false;
    _red = id < 16;

    if(_red){
        _row = pos[id].row;
        _col = pos[id].col;
        _type = pos[id].type;
        _bUpside = true;
    } else{
        _row = 9 - pos[id - 16].row;
        _col = 8 - pos[id - 16].col;
        _type = pos[id - 16].type;
        _bUpside = false;
    }
}

void Stone::rotate()
{
    _bUpside = !_bUpside;
    _row = 9 - _row;
    _col = 8 - _col;
}


QString Stone::getText()
{
    switch (_type) {
    case JIANG:
        if (_red)
            return "帥";
        else
            return "將";

    case JU:
        return "車";

    case PAO:
        return "炮";

    case MA:
        return "馬";

    case BING:
        if (_red)
            return "兵";
        else
            return "卒";

    case SHI:
        return "士";

    case XIANG:
        if (_red)
            return "相";
        else
            return "象";
    }
    return "错误";
}
