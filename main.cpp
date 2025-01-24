#include "passwordWindow.h"
#include "main.h"

#include <QApplication>
#include <QStyleFactory>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qApp->setStyle(QStyleFactory::create("Fusion"));
    PasswordWindow w;
    w.show();
    return a.exec();
}
