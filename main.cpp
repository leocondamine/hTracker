#include "htracker.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    hTracker w;
    w.show();
    return a.exec();
}
