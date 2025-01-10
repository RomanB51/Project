#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Entry_clicked()
{
    QString login = ui->lineEdit_login->text();
    QString password = ui->lineEdit_password->text();

    if(login == "" && password == ""){
        this->hide();
        secondWindow = new SecondWindow();
        secondWindow->show();
    }
    else{
        QMessageBox::information(this, "Ошибка авторизации", "Логин или пароль введены неверно");
    }
}


void MainWindow::on_pushButton_Escape_clicked()
{
    this->close();
}

