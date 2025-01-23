#include "passwordWindow.h"
#include "ui_passwordWindow.h"

#include "mainWindow.h"


#include <QMessageBox>
#include <QKeyEvent>
#include <QEvent>
#include <QAction>
#include <QLineEdit>

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

    qDebug() << "Окно пароля создано";
}

PasswordWindow::~PasswordWindow()
{
    qDebug() << "Окно пароля уничтожено";
    delete ui;
}


void PasswordWindow::Show_Hide_Password(){
    if(flag_for_show_hide){
        customAction->setIcon(QIcon(":/Images/Icons/Show.png"));
        customAction->setToolTip("Показать пароль");
        ui->lineEdit_password->setEchoMode(QLineEdit::Password);
        flag_for_show_hide = 0;
    }
    else{
        customAction->setIcon(QIcon(":/Images/Icons/Hide.png"));
        customAction->setToolTip("Скрыть пароль");
         ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
         flag_for_show_hide = 1;
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
        mainWindow = new MainWindow(this, second_name, first_name, otchestvo);
        connect(mainWindow, &MainWindow::showPasswordWindow, this, &PasswordWindow::ShowMe);
        mainWindow->show();
    }
    else if(login == "1" && password == "1"){
        this->hide();
        QString first_name = "Василий";
        QString second_name = "Вахрамеев";
        QString otchestvo = "Евгеньевич";
        mainWindow = new MainWindow(this, second_name, first_name, otchestvo);
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
    QApplication::quit();
}

