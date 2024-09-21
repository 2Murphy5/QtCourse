#include "qwmainwind.h"  // Correct header file

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWMainWind w;  // Corrected class name
    w.show();
    return a.exec();
}
