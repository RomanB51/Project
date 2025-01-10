#include "passwordWindow.h"
#include "ui_passwordWindow.h"
#include <QMessageBox>

PasswordWindow::PasswordWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PasswordWindow)
{
    ui->setupUi(this);
}

PasswordWindow::~PasswordWindow()
{
    delete ui;
}


void PasswordWindow::on_pushButton_Entry_clicked()
{
    QString login = ui->lineEdit_login->text();
    QString password = ui->lineEdit_password->text();

    if(login == "" && password == ""){
        this->hide();
        mainWindow = new MainWindow();
        mainWindow->show();
    }
    else{
        QMessageBox::information(this, "Ошибка авторизации", "Логин или пароль введены неверно");
    }
}


void PasswordWindow::on_pushButton_Escape_clicked()
{
    this->close();
}

