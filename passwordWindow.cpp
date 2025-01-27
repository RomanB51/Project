#include "passwordWindow.h"
#include "ui_passwordWindow.h"

#include "mainWindow.h"


#include <QMessageBox>
#include <QKeyEvent>
#include <QEvent>
#include <QAction>
#include <QLineEdit>
#include <QDir>

PasswordWindow::PasswordWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PasswordWindow)
{
    ui->setupUi(this);

    ui->lineEdit_login->installEventFilter(this);
    ui->lineEdit_password->installEventFilter(this);
    ui->pushButton_Entry->installEventFilter(this);
    ui->pushButton_Entry->setAutoDefault(0);
    ui->pushButton_Exit->setAutoDefault(0);
    customAction = new QAction("Custom Action", ui->lineEdit_password);
    customAction->setIcon(QIcon(":/Images/Icons/Show.png"));
    customAction->setToolTip("Показать пароль");
    ui->lineEdit_password->addAction(customAction, QLineEdit::TrailingPosition);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    connect(customAction, &QAction::triggered, this, &PasswordWindow::Show_Hide_Password);

    qApp->setWindowIcon(QIcon(":/Images/Icons/WindowIcon.jpg"));

    qDebug() << "Окно пароля создано";

    QDir programmDir = QDir::current();
    programmDir.cdUp();
    programmDir.cdUp();
    QString file_path = programmDir.absoluteFilePath("Configuration of DB.txt");

    QFile file(file_path);
    if(file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"Файл открыт";
        read_data_about_DB(file);

    }
    else{
        qDebug()<<"Файл создан";
        file.open(QFile::WriteOnly | QFile::Text);
        QTextStream out(&file);
        out << "Ip adress = 'insert here ip adress of your DB'\n"
               "Username in DB = 'insert here username in your DB'\n"
               "Name of DB = 'insert here name of your DB'\n"
               "Name of table = 'insert here name of table'";
        file.flush();
        file.close();
        QMessageBox::information(this, "Ошибка подключения", "Файл 'Configuration of DB' вероятно был удален.\
                                                              Введите в нем необходимые данные и перезапустите приложение.");
        qApp->quit();
    }
}

PasswordWindow::~PasswordWindow()
{
    qDebug() << "Окно пароля уничтожено";
    delete ui;
}


void PasswordWindow::Show_Hide_Password(){
    flag_for_show_hide_password = !flag_for_show_hide_password;

    if(flag_for_show_hide_password){
        customAction->setIcon(QIcon(":/Images/Icons/Show.png"));
        customAction->setToolTip("Показать пароль");
        ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    }
    else{
        customAction->setIcon(QIcon(":/Images/Icons/Hide.png"));
        customAction->setToolTip("Скрыть пароль");
        ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
    }
}

bool PasswordWindow::eventFilter(QObject *obj, QEvent *evt){
        if(evt->type() == QKeyEvent::KeyRelease){
            if(flag_for_focus_enter_after_QMessage){
                QKeyEvent *keyEvent = static_cast<QKeyEvent *>(evt);
                if(keyEvent->key() == Qt::Key_Return && !ui->pushButton_Entry->hasFocus()){
                    QKeyEvent ke(QEvent::KeyPress, Qt::Key_Tab, Qt::NoModifier);
                    QCoreApplication::sendEvent(this, &ke);
                }
                if(ui->pushButton_Entry->hasFocus()){
                    on_pushButton_Entry_clicked();
                }
            }
            else
               flag_for_focus_enter_after_QMessage = 1;
        }
    return QDialog::eventFilter(obj, evt);
}

void PasswordWindow::ShowMe()
{
    this->show();
}


void PasswordWindow::on_pushButton_Entry_clicked()
{
    QString login = ui->lineEdit_login->text();
    QString password = ui->lineEdit_password->text();


    if(login == "" && password == ""){
        this->hide();
        QString first_name = "Роман";
        QString second_name = "Бычков";
        QString otchestvo = "Евгеньевич";
        QString ip_adress = data_about_DB[0];
        flag_admin_user = 0;
        mainWindow = new MainWindow(this, second_name, first_name, otchestvo, ip_adress, flag_admin_user);
        connect(mainWindow, &MainWindow::showPasswordWindow, this, &PasswordWindow::ShowMe);
        mainWindow->show();
    }
    else if(login == "1" && password == "1"){
        this->hide();
        QString first_name = "Василий";
        QString second_name = "Вахрамеев";
        QString otchestvo = "Евгеньевич";
        QString ip_adress = data_about_DB[0];
        flag_admin_user = 1;
        mainWindow = new MainWindow(this, second_name, first_name, otchestvo, ip_adress, flag_admin_user);
        connect(mainWindow, &MainWindow::showPasswordWindow, this, &PasswordWindow::ShowMe);
        mainWindow->show();
        }
        else{
            QMessageBox::information(this, "Ошибка авторизации", "Логин или пароль введены неверно");
            flag_for_focus_enter_after_QMessage = 0;
            ui->lineEdit_password->setFocus();
            ui->lineEdit_password->clear();
        }
        ui->lineEdit_login->clear();
        ui->lineEdit_password->clear();
        ui->lineEdit_login->setFocus();
}


void PasswordWindow::on_pushButton_Exit_clicked()
{
    qApp->quit();
}

void PasswordWindow::read_data_about_DB(QFile &object)
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

