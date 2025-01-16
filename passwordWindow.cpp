#include "./passwordWindow.h"
#include "./ui_passwordWindow.h"
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
    ui->pushButton_Escape->setAutoDefault(0);
    QAction *customAction = new QAction("Custom Action", ui->lineEdit_password);
    customAction->setIcon(QIcon("D:/C++/My_project/Project/Show.png"));
    ui->lineEdit_password->addAction(customAction, QLineEdit::TrailingPosition);
}

PasswordWindow::~PasswordWindow()
{
    delete ui;
}


bool flag_for_focus_enter_after_QMessage = 1;

bool PasswordWindow::eventFilter(QObject *obj, QEvent *evt){
        if(evt->type() == QKeyEvent::KeyRelease){
            if(flag_for_focus_enter_after_QMessage){
                QKeyEvent *keyEvent = static_cast<QKeyEvent *>(evt);
                if(keyEvent->key() == Qt::Key_Return && !ui->pushButton_Entry->hasFocus()){
                    QKeyEvent ke(QEvent::KeyPress, Qt::Key_Tab, Qt::NoModifier);
                    QCoreApplication::sendEvent(this, &ke);
                }
                if(ui->pushButton_Entry->hasFocus())
                    on_pushButton_Entry_clicked();
            }
            else
                flag_for_focus_enter_after_QMessage = 1;
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
        flag_for_focus_enter_after_QMessage = 0;
        ui->lineEdit_login->setFocus();
        ui->lineEdit_login->selectAll();
    }
}


void PasswordWindow::on_pushButton_Escape_clicked()
{
    this->close();
}

