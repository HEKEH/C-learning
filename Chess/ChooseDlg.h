#ifndef CHOOSEDLG_H
#define CHOOSEDLG_H
#include <QDialog>
#include <QPushButton>


class ChooseDlg : public QDialog
{
    Q_OBJECT
public:
    ChooseDlg(QWidget* parent = 0);
    QPushButton* _buttons[4];
    int _selected;
public slots:
    void onClicked();
};


#endif // CHOOSEDLG_H
