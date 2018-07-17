#include "CtrlPanel.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <stdio.h>

CtrlPanel::CtrlPanel(QWidget *parent) : QWidget(parent)
{
    QGridLayout* grid = new QGridLayout(this);

    QVBoxLayout* _Vlay = new QVBoxLayout;
    _back = new QPushButton("back");
    _Vlay->addWidget(_back);

    grid->addLayout(_Vlay, 1, 1);

    grid->setColumnStretch(0, 1);
    grid->setColumnStretch(2, 1);
    grid->setRowStretch(0, 1);
    grid->setRowStretch(2, 1);

    connect(_back, SIGNAL(clicked()), this, SIGNAL(sigBack()));

}

