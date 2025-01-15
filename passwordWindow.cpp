#include "./passwordWindow.h"
#include "./ui_passwordWindow.h"
#include <QMessageBox>
#include <QKeyEvent>
#include <QEvent>

PasswordWindow::PasswordWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PasswordWindow)
{
    ui->setupUi(this);
    ui->lineEdit_login->installEventFilter(this);
    ui->lineEdit_password->installEventFilter(this);
    ui->lineEdit_password->home(0);
}

PasswordWindow::~PasswordWindow()
{
    delete ui;
}

bool PasswordWindow::eventFilter(QObject *obj, QEvent *evt){
    if(evt->type() == QKeyEvent::KeyRelease){
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(evt);
        if(ui->lineEdit_login->hasFocus() && keyEvent->key() == Qt::Key_Return){
            ui->lineEdit_password->setFocus();
            ui->lineEdit_password->setCursorPosition(0);
        }
        if(ui->lineEdit_password->hasFocus() && keyEvent->key() == Qt::Key_Return){
            ui->pushButton_Entry->setFocus();
        }
    }
    return QDialog::eventFilter(obj, evt);
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

