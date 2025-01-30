#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include "passwordWindow.h"

#include <QApplication>
#include <QDir>

class MyApplication:public QApplication
{
    Q_OBJECT
public:
    MyApplication(int &argc, char **argv);

    ~MyApplication();

    int Check_config_file();

    int RunApp();

    void Read_data_about_DB(QFile &object);

private:

    int flag_startUp;

    PasswordWindow *passwordWindow;

    std::vector<QString> data_about_DB = {"", "", "", ""};
};

#endif // MYAPPLICATION_H
