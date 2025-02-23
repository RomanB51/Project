#include "filterWindow.h"
#include "ui_filterWindow.h"


#include "mainWindow.h"

FilterWindow::FilterWindow(QWidget *parent, QString second_name, QString first_name, QString otchestvo, QString file_name,\
                           QString date, QString counter_last_report)
    : QMainWindow(parent)
    , ui(new Ui::FilterWindow)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);

    ui->lineEdit_Second_name->setFocus();
    ui->pushButton_Find_reports->setAutoDefault(0);
    ui->pushButton_Cancel->setAutoDefault(0);
    ui->pushButton_CleanAll->setAutoDefault(0);

    ui->lineEdit_Second_name->installEventFilter(this);
    ui->lineEdit_First_name->installEventFilter(this);
    ui->lineEdit_Otchestvo->installEventFilter(this);
    ui->lineEdit_File_name->installEventFilter(this);
    ui->dateEdit->installEventFilter(this);
    ui->spinBox->installEventFilter(this);


    ui->lineEdit_Second_name->setText(second_name);
    ui->lineEdit_First_name->setText(first_name);
    ui->lineEdit_Otchestvo->setText(otchestvo);
    ui->lineEdit_File_name->setText(file_name);

    if(date == "")
        ui->dateEdit->setDate(QDate::currentDate());
    else
        ui->dateEdit->setDate(QDate::fromString(date, "dd.MM.yyyy"));
    ui->spinBox->setValue(counter_last_report.toInt());

    qDebug()<<"Окно фильтров создано";
}

FilterWindow::~FilterWindow()
{
    qDebug()<<"Окно фильтров уничтожено";
    delete ui;
}

void FilterWindow::on_pushButton_Find_reports_clicked()
{
    MainWindow::Set_filter_second_name(ui->lineEdit_Second_name->text());
    MainWindow::Set_filter_first_name(ui->lineEdit_First_name->text());
    MainWindow::Set_filter_otchestvo(ui->lineEdit_Otchestvo->text());
    MainWindow::Set_filter_file_name(ui->lineEdit_File_name->text());

    if(ui->checkBox_Date->isChecked())
        MainWindow::Set_filter_date(ui->dateEdit->text());
    else
        MainWindow::Set_filter_date("");

    MainWindow::Set_filter_counter_last_report(ui->spinBox->text());
    emit showDate();
    this->close();
}


void FilterWindow::on_pushButton_Cancel_clicked()
{
    this->close();
}


void FilterWindow::on_pushButton_CleanAll_clicked()
{
    ui->lineEdit_Second_name->clear();
    ui->lineEdit_First_name->clear();
    ui->lineEdit_Otchestvo->clear();
    ui->lineEdit_File_name->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->spinBox->setValue(0);
}

bool FilterWindow::eventFilter(QObject *obj, QEvent *evt)
{
    if(evt->type() == QKeyEvent::KeyRelease){
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(evt);
            if(keyEvent->key() == Qt::Key_Return){
                QKeyEvent ke(QEvent::KeyPress, Qt::Key_Tab, Qt::NoModifier);
                QCoreApplication::sendEvent(this, &ke);
                if(ui->checkBox_Date->hasFocus() || ui->pushButton_CleanAll->hasFocus())
                    QCoreApplication::sendEvent(this, &ke);
            }
            if(ui->pushButton_Find_reports->hasFocus()){
                on_pushButton_Find_reports_clicked();
            }
    }
    return QMainWindow::eventFilter(obj, evt);
}

