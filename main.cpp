#include "passwordWindow.h"
#include "main.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PasswordWindow w;
    w.show();
    return a.exec();
}
