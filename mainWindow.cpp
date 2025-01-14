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
    ui->tableWidget->setRowCount(5);
    QList<QString> name_column_list_report = {"Имя файла", "Путь к файлу", "Дата", "Время", "Фамилия", "Имя", "Отчество"};
    QList<QString> name_column_list_result = {"а", "б", "в", "г", "д", "е", "ё", "ж", "з", "и", "й", "к", "л", "м", "н", \
    "о", "п", "р", "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я"};
    ui->tableWidget->setHorizontalHeaderLabels(name_column_list_report);
    ui->tableWidget->setColumnWidth(1, 300);
    ui->statusbar->showMessage("Бычков Роман Евгеньевич");
    this->resize(900, 600);


}

MainWindow::~MainWindow()
{
    delete ui;
}


// struct Stroka{
//     QString struct_file_path;
//     QString struct_date_as_string;
//     QString struct_time_as_string;
//     QString struct_second_name;
//     QString struct_first_name;
//     QString struct_otchestvo;
// };
std::map <QString, std::vector <QString>> stroka;
    int counter_row = 0;

void MainWindow::on_pushButton_ChooseFile_clicked()
{
    QString filter = "Text File (*.txt)";
    QString file_path = QFileDialog::getOpenFileName(this, "Окно выбора файлов", "D:/C++/", filter);
    QFileInfo fileinfo(file_path);
    QString file_name = fileinfo.baseName();

    QFile file(file_path);
    if(!file.open(QFile::ReadOnly | QFile::Text)){ //Проверка на то, можем ли мы что-либо считывать
        QMessageBox::warning(this, "Title", "Не удалось открыть файл");
    }

    QString first_name = "Роман";
    QString second_name = "Бычков";
    QString otchestvo = "Евгеньевич";
    QString time = QTime::currentTime().toString("hh : mm : ss");
    QString date = QDate::currentDate().toString("dd.MM.yyyy");
    std::vector <QString> vec_stroka = {file_path, time, date, second_name, first_name, otchestvo};

    //Stroka struct_str = {file_path, time, date, second_name, first_name, otchestvo};
    //stroka[file_name] = struct_str;
    stroka[file_name] = vec_stroka;

    QTableWidgetItem *column_file_name = new QTableWidgetItem(file_name);
    column_file_name->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(counter_row, 0, column_file_name);
    for(int i = 1; i != ui->tableWidget->columnCount(); i++){
        QTableWidgetItem *column = new QTableWidgetItem(vec_stroka[i-1]);
        column->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(counter_row, i, column);
    }
    counter_row++;
    // QTableWidgetItem *column_file_path = new QTableWidgetItem(file_path);
    // column_file_path->setTextAlignment(Qt::AlignCenter);
    // ui->tableWidget->setItem(counter_row, 1, column_file_path);
    // QTableWidgetItem *column_time = new QTableWidgetItem(time_as_string);
    // column_time->setTextAlignment(Qt::AlignCenter);
    // ui->tableWidget->setItem(counter_row, 2, column_time);
    // QTableWidgetItem *column_date = new QTableWidgetItem(date_as_string);
    // column_date->setTextAlignment(Qt::AlignCenter);
    // ui->tableWidget->setItem(counter_row, 3, column_date);
    // QTableWidgetItem *column_second_name = new QTableWidgetItem(second_name);
    // column_second_name->setTextAlignment(Qt::AlignCenter);
    // ui->tableWidget->setItem(counter_row, 4, column_second_name);
    // QTableWidgetItem *column_first_name = new QTableWidgetItem(first_name);
    // column_first_name->setTextAlignment(Qt::AlignCenter);
    // ui->tableWidget->setItem(counter_row, 5, column_first_name);
    // QTableWidgetItem *column_otchestvo = new QTableWidgetItem(otchestvo);
    // column_otchestvo->setTextAlignment(Qt::AlignCenter);
    // ui->tableWidget->setItem(counter_row, 6, column_otchestvo);



    //stroka[file_name] = {file_path, date_as_string, time_as_string, second_name, first_name, otchestvo};

    // for(int column = 0; column != ui->tableWidget->columnCount(); column++){
    //     QTableWidgetItem *item = new QTableWidgetItem(stroka[file_name][column]);
    //     item->setTextAlignment(Qt::AlignCenter);
    //     ui->tableWidget->setItem(counter_row, column, item);
    // }


    // QTextStream in(&file);
    // QString *k;
    // int g = 0;
    // while(in.readLineInto(k, 1))
    //     if(k == "о")
    //         g++;
    // qDebug() << g;

    // QString text = in.readAll();
    // qDebug() << text;
    file.close();
}

