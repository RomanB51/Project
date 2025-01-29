#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include "passwordWindow.h"

#include <QApplication>
#include <QDir>

class MyApplication:public QApplication
{
public:
    MyApplication(int &argc, char **argv);

    ~MyApplication();

    bool Check_config_file();

    int RunApp();

private:

    bool flag_startUp;

    PasswordWindow *passwordWindow;
};

#endif // MYAPPLICATION_H
