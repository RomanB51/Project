
#include "myApplication.h"

#include <QApplication>
#include <QStyleFactory>



int main(int argc, char *argv[])
{
    MyApplication a(argc, argv);
    qApp->setStyle(QStyleFactory::create("Fusion"));

    return a.RunApp();
}
