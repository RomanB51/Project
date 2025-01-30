#include "myApplication.h"


#include <QDir>
#include <QMessageBox>
#include <QTextStream>

MyApplication::MyApplication(int &argc, char **argv)
    :QApplication(argc, argv)
{
    this->flag_startUp = Check_config_file();
}

MyApplication::~MyApplication()
{
    qDebug() << "Деструктор вызван";
    delete passwordWindow;
}


int MyApplication::Check_config_file()
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
        out << "Ip adress = 'insert here ip adress of your DB'\n"
               "Username in DB = 'insert here username in your DB'\n"
               "Name of DB = 'insert here name of your DB'\n"
               "Name of table = 'insert here name of table'";
        file.flush();
        file.close();
        QMessageBox *msg = new QMessageBox();
        msg->setText("Файл 'Configuration of DB' вероятно был удален.\n\
                    Введите в нем необходимые данные и перезапустите приложение.");
        msg->setWindowTitle("Ошибка подключения");
        msg->exec();
        return 0;
    }
}

int MyApplication::RunApp()
{
    if(flag_startUp){
        passwordWindow = new PasswordWindow(data_about_DB);
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
