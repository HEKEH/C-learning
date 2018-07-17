#include "ChooseDlg.h"
#include <QVBoxLayout>

ChooseDlg::ChooseDlg(QWidget* parent) : QDialog(parent)
{
    QVBoxLayout* VLay = new QVBoxLayout(this);
    VLay->addWidget(_buttons[0] = new QPushButton("人机对战"));
    VLay->addWidget(_buttons[1] = new QPushButton("人人对战"));
    VLay->addWidget(_buttons[2] = new QPushButton("网络对战(服务端)"));
    VLay->addWidget(_buttons[3] = new QPushButton("网络对战(客户端)"));

    for (int i = 0; i < 4; i++)
    {
        connect(_buttons[i], SIGNAL(clicked()), this, SLOT(onClicked()));
    }
}

void ChooseDlg::onClicked()
{
    QObject* s = sender();
    for (int i = 0; i < 4; i++)
    {
        if (s == _buttons[i])
        {
            _selected = i;
        }
    }
    accept();
}
