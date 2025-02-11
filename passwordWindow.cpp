#include "passwordWindow.h"
#include "ui_passwordWindow.h"

#include "mainWindow.h"


#include <QMessageBox>
#include <QKeyEvent>
#include <QEvent>
#include <QAction>
#include <QLineEdit>
#include <pqxx/pqxx>


PasswordWindow::PasswordWindow(std::vector<QString> data_about_DB, pqxx::connection *conn, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PasswordWindow)
{
    ui->setupUi(this);

    conn_for_password = conn;

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

    this->info_about_DB = data_about_DB;

    qDebug() << "Окно пароля создано";
}

PasswordWindow::~PasswordWindow()
{
    conn_for_password->close();
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


    pqxx::work transaction(*conn_for_password);
    pqxx::result res = transaction.exec("select id, positions, second_name, first_name, third_name from staff where login LIKE '" + login.toStdString() + "' and password LIKE '" + password.toStdString() + "';");
    transaction.commit();
    if(!res.empty()){
        for (pqxx::result::const_iterator row = res.begin(); row != res.end(); ++row){
            this->id_staff = QString::fromStdString(row[0].as<std::string>());
            this->position = QString::fromStdString(row[1].as<std::string>());
            this->second_name = QString::fromStdString(row[2].as<std::string>());
            this->first_name = QString::fromStdString(row[3].as<std::string>());
            this->otchestvo = QString::fromStdString(row[4].as<std::string>());
        }
        if(position == "Ведущий инженер")
            flag_admin_user = 1;
        else
            flag_admin_user = 0;


        ip_adress = info_about_DB[3];
        this->hide();
        mainWindow = new MainWindow(this, this->second_name, this->first_name, this->otchestvo, this->ip_adress,\
                                    this->flag_admin_user, this->id_staff, conn_for_password);
        connect(mainWindow, &MainWindow::showPasswordWindow, this, &PasswordWindow::ShowMe);
        mainWindow->show();

        ui->lineEdit_login->clear();
        ui->lineEdit_password->clear();
        ui->lineEdit_login->setFocus();
    }
    else{
            QMessageBox::information(this, "Ошибка авторизации", "Логин или пароль введены неверно");
            flag_for_focus_enter_after_QMessage = 0;
            ui->lineEdit_password->setFocus();
            ui->lineEdit_password->clear();
    }


}


void PasswordWindow::on_pushButton_Exit_clicked()
{
    qApp->quit();
}

