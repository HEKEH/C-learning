#ifndef STONE_H
#define STONE_H
#include <QString>



class Stone
{
public:
    Stone();
    //~Stone();

    enum TYPE{JIANG, JU, PAO, MA, BING, SHI, XIANG};
    int _row;
    int _col;
    TYPE _type;

    int _id;
    bool _dead;
    bool _red;
    bool _bUpside;

    struct{
        int row, col;
        TYPE type;
    }pos[16] = {
    {0, 0, JU},
    {0, 1, MA},
    {0, 2, XIANG},
    {0, 3, SHI},
    {0, 4, JIANG},
    {0, 5, SHI},
    {0, 6, XIANG},
    {0, 7, MA},
    {0, 8, JU},
    {2, 1, PAO},
    {2, 7, PAO},
    {3, 0, BING},
    {3, 2, BING},
    {3, 4, BING},
    {3, 6, BING},
    {3, 8, BING},
    };

    void init(int id);
    void rotate();
    QString getText();

};

#endif // STONE_H
