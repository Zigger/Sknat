#include "tgraphics.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TGraphics w;

    w.show();
    
    return a.exec();
}
