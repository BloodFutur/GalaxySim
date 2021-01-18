#include "widget.h"
#include "triangletest.h"
#include "galaxy.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    QSurfaceFormat format;
    format.setSamples(16);

    TriangleTest window;
    window.setFormat(format);
    window.resize(640, 480);
    window.show();
    window.setAnimating(true);

    Galaxy galaxy;
    galaxy.setFormat(format);
    galaxy.resize(640,480);
    galaxy.show();
    galaxy.setAnimating(true);

    return a.exec();
}
