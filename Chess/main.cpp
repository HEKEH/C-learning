#include <QApplication>
#include "MainWnd.h"
#include "ChooseDlg.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    ChooseDlg dlg;
    if (dlg.exec() != QDialog :: Accepted)
    {
        return 0;
    }
    MainWnd window(dlg._selected);
    window.show();
    return app.exec();
}
