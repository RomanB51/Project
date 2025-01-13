#include "./mainWindow.h"
#include "./ui_mainWindow.h"
#include "main.h"
#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <map>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setRowCount(5);
    QList<QString> name_column_list_report = {"Имя файла", "Путь к файлу", "Дата", "Время", "Фамилия", "Имя", "Отчество"};
    QList<QString> name_column_list_result = {"а", "б", "в", "г", "д", "е", "ё", "ж", "з", "и", "й", "к", "л", "м", "н", \
    "о", "п", "р", "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я"};
    ui->tableWidget->setHorizontalHeaderLabels(name_column_list_report);
    //ui->tableWidget->setColumnWidth(0, 10);

    //for(int i = 6; i != ui->tableWidget->columnCount(); ++i)
        //ui->tableWidget->setColumnWidth(i, 15);
    //ui->tableWidget->verticalHeader()->setVisible(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}
struct Stroka{
    QString struct_file_path;
    QString struct_date_as_string;
    QString struct_time_as_string;
    QString struct_second_name;
    QString struct_first_name;
    QString struct_otchestvo;
};
std::map <QString, Stroka> stroka;
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

    counter_row++;
    QString first_name = "Роман";
    QString second_name = "Бычков";
    QString otchestvo = "Евгеньевич";
    QTime time = QTime::currentTime();
    QString time_as_string = time.toString("hh : mm : ss");
    QDate date = QDate::currentDate();
    QString date_as_string = date.toString("dd.MM.yyyy");

    Stroka struct_str = {file_path, date_as_string, time_as_string, second_name, first_name, otchestvo};

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

