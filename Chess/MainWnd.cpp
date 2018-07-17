#include "MainWnd.h"
#include "SingleGame.h"
#include "MultiGame.h"
#include "NetGame.h"
#include <QHBoxLayout>

MainWnd::MainWnd(int gameType, QWidget *parent) : QWidget(parent)
{
    CtrlPanel* panel = new CtrlPanel;
    QHBoxLayout* HLay = new QHBoxLayout(this);

    switch(gameType)
    {
        case 0:
        {
        SingleGame* game = new SingleGame;
        HLay->addWidget(game, 1);
        HLay->addWidget(panel);
        connect(panel, SIGNAL(sigBack()), game, SLOT(slotBack()));
        break;
        }

        case 1:
        {
        MultiGame* game = new MultiGame;
        HLay->addWidget(game, 1);
        HLay->addWidget(panel);
        connect(panel, SIGNAL(sigBack()), game, SLOT(slotBack()));
        break;
        }

        case 2:
        {
        NetGame* game = new NetGame(true);
        HLay->addWidget(game, 1);
        HLay->addWidget(panel);
        connect(panel, SIGNAL(sigBack()), game, SLOT(slotBack()));
        break;
        }

        case 3:
        {
        NetGame* game = new NetGame(false);
        HLay->addWidget(game, 1);
        HLay->addWidget(panel);
        connect(panel, SIGNAL(sigBack()), game, SLOT(slotBack()));
        break;
        }
    }

    return;
}
