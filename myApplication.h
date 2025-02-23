#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include "passwordWindow.h"

#include <QApplication>
#include <QDir>
#include <pqxx/pqxx>

class MyApplication:public QApplication
{
    Q_OBJECT
public:
    MyApplication(int &argc, char **argv);

    ~MyApplication();

    bool Check_config_file();

    bool Check_connection_DB();

    int RunApp();

    void Read_data_about_DB(QFile &object);

private:

    bool flag_config_file = 0;

    bool flag_connection = 0;

    PasswordWindow *passwordWindow;

    std::vector<QString> data_about_DB = {"", "", "", "", ""};

    pqxx::connection *conn = nullptr;
};

#endif // MYAPPLICATION_H
