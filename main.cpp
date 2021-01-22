#include "widget.h"
#include "triangletest.h"
#include "galaxy.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);

    Galaxy galaxy;
    galaxy.setFormat(format);
    galaxy.resize(1000,1000);
    galaxy.show();
    galaxy.setAnimating(true);

    /*
    Widget w;
    w.show();

    TriangleTest window;
    window.setFormat(format);
    window.resize(640, 480);
    window.show();
    window.setAnimating(true);
    */


    return a.exec();
}
