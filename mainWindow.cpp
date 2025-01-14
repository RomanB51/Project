#include "./mainWindow.h"
#include "./ui_mainWindow.h"
#include "main.h"
#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QGuiApplication>
#include <map>
#include <string>
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(7);
    QList<QString> name_column_list_report = {"Имя файла", "Путь к файлу", "Дата", "Время", "Фамилия", "Имя", "Отчество"};
    QList<QString> name_column_list_result = {"а", "б", "в", "г", "д", "е", "ё", "ж", "з", "и", "й", "к", "л", "м", "н", \
    "о", "п", "р", "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я"};
    ui->tableWidget->setHorizontalHeaderLabels(name_column_list_report);
    ui->statusbar->showMessage("Бычков Роман Евгеньевич");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);



}

MainWindow::~MainWindow()
{
    delete ui;
}

std::map <QString, std::vector <QString>> stroka;
int counter_row = 0;


void MainWindow::on_pushButton_ChooseFile_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Окно выбора файлов", "D:/C++/", "Text File (*.txt)");

    QFile file(file_path);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
    }
    else{
        counter_row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(counter_row);
        QFileInfo file_info(file_path);
        QString file_name = file_info.baseName();
        QString first_name = "Роман";
        QString second_name = "Бычков";
        QString otchestvo = "Евгеньевич";
        QString time = QTime::currentTime().toString("hh : mm : ss");
        QString date = QDate::currentDate().toString("dd.MM.yyyy");
        stroka[file_name] = {file_path, time, date, second_name, first_name, otchestvo};


        QTableWidgetItem *column_file_name = new QTableWidgetItem(file_name);
        column_file_name->setTextAlignment(Qt::AlignCenter);
        column_file_name->setToolTip(file_name);
        ui->tableWidget->setItem(counter_row, 0, column_file_name);

        for(int i = 1; i != ui->tableWidget->columnCount(); i++){
            QTableWidgetItem *column = new QTableWidgetItem(stroka[file_name][i-1]);
            column->setToolTip(stroka[file_name][i-1]);
            column->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(counter_row, i, column);
        }
        file.close();
    }
}



void MainWindow::on_pushButton_Close_clicked()
{
    this->close();
}




void MainWindow::on_pushButton_Delete_str_clicked()
{
    int index_del_row = ui->tableWidget->currentRow();
    QTableWidgetItem *column_file_name = ui->tableWidget->item(index_del_row, 0);
    QTableWidgetItem *column_time = ui->tableWidget->item(index_del_row, 3);
    QString file_name_del_row = column_file_name->text();
    QString time_del_row = column_time->text();

    QMessageBox::warning(this, "Строка", file_name_del_row);
    stroka.erase(file_name_del_row);
    ui->tableWidget->removeRow(index_del_row);
}

