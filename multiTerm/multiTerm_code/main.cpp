#include "multiterm.h"

#include <QApplication>
#include <QFile>
#include <QMessageBox>


//--------------------------------------------
//
//      main
//
//--------------------------------------------
int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MultiTerm w;
    w.show();
    return application.exec();
}
