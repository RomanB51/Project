#include "myApplication.h"


#include <QDir>
#include <QMessageBox>
#include <QTextStream>

MyApplication::MyApplication(int &argc, char **argv)
    :QApplication(argc, argv)
{
    this->flag_config_file = Check_config_file();
    if(flag_config_file)
        this->flag_connection = Check_connection_DB();
}

MyApplication::~MyApplication()
{
    conn->close();
    qDebug() << "Деструктор вызван";
    delete passwordWindow;
}


bool MyApplication::Check_config_file()
{
    QDir programmDir = QDir::current();
    programmDir.cdUp();
    programmDir.cdUp();
    QString file_path = programmDir.absoluteFilePath("Configuration of DB.txt");

    QFile file(file_path);
    if(file.open(QFile::ReadOnly | QFile::Text))
    {
        Read_data_about_DB(file);
        file.close();
        return 1;
    }
    else{
        file.open(QFile::WriteOnly | QFile::Text);
        QTextStream out(&file);
        out <<  "Name of DB = 'insert here name of your DB'\n"
                "Username in DB = 'insert here username in your DB'\n"
                "Password of user = 'insert here password of user'\n"
                "Ip adress = 'insert here ip adress of your DB'\n"
                "Port = 'insert here port's number of DB'";
        file.flush();
        file.close();
        QMessageBox *msg = new QMessageBox();
        msg->setText("Файл 'Configuration of DB' вероятно был удален.\n"
                    "Введите в нем необходимые данные и перезапустите приложение.");
        msg->setWindowTitle("Ошибка подключения");
        msg->exec();
        return 0;
    }
}

int MyApplication::RunApp()
{
    if(flag_config_file * flag_connection){
        passwordWindow = new PasswordWindow(data_about_DB, conn);
        passwordWindow->show();
        return exec();
    }
    else{
        return 1;
    }
}

void MyApplication::Read_data_about_DB(QFile &object)
{
    QTextStream in(&object);
    QString symbol;
    QString* ptr_symbol = &symbol;
    int i = 0;


    while(in.readLineInto(ptr_symbol, 1)){
        if(*ptr_symbol == "'"){
            in.readLineInto(ptr_symbol, 1);
            while(*ptr_symbol != "'"){
                data_about_DB[i] += *ptr_symbol;
                in.readLineInto(ptr_symbol, 1);
            }
            i++;
        }
    }
    object.close();
}


bool MyApplication::Check_connection_DB()
{
    QString information_about_connect = "dbname=" + data_about_DB[0] + " user=" + data_about_DB[1] + " password=" +\
                                        data_about_DB[2] + " hostaddr=" + data_about_DB[3] + " port=" + data_about_DB[4];
    conn = new pqxx::connection(information_about_connect.toStdString());
    if(conn->is_open()){
        qDebug() << "Connected to PostgreSQL successfully.";
        return 1;
    }
    else{
        qDebug() << "Failed to connect to PostgreSQL.";
        QMessageBox *msg = new QMessageBox();
        msg->setText("Не удалось подключиться к базе данных.\n\
                     Убедитесь в правильности данных в конфигурационном файле.");
        msg->setWindowTitle("Ошибка подключения");
        msg->exec();
        return 0;
    }
}

