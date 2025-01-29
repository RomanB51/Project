#include "myApplication.h"


#include <QDir>
#include <QMessageBox>

MyApplication::MyApplication(int &argc, char **argv):QApplication(argc, argv){
    flag_startUp = Check_config_file();
};

MyApplication::~MyApplication()
{
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
        msg->setText("Файл 'Configuration of DB' вероятно был удален.\
                    Введите в нем необходимые данные и перезапустите приложение.");
        msg->setWindowTitle("Ошибка подключения");
        msg->exec();
        return 0;
    }
}

int MyApplication::RunApp()
{
    if(flag_startUp){
        passwordWindow = new PasswordWindow();
        passwordWindow->show();
        return exec();
    }
    else{
        return 1;
    }
}
