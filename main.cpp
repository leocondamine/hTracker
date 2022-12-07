#include "htracker.h"

#include <QApplication>
#include <QFile>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile cssFile(QDir::currentPath() + "/SyNet.qss");
    cssFile.open(QFile::ReadOnly);
    QString css = QLatin1String(cssFile.readAll());
    a.setStyleSheet(css);

    hTracker w;
    w.show();
    return a.exec();
}
