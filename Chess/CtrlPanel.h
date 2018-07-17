#ifndef CTRLPANEL_H
#define CTRLPANEL_H

#include <QWidget>
#include <QPushButton>

class CtrlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CtrlPanel(QWidget *parent = nullptr);
    QPushButton* _back;
//    QVBoxLayout* _Vlay;

signals:
    void sigBack();

public slots:

};

#endif // CTRLPANEL_H
