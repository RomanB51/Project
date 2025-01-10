#include "mainWindow.h"
#include "ui_mainWindow.h"
#include "main.h"
#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(5);
    QList<QString> name_column_list_report = {"№", "Фамилия", "Имя", "Отчество", "Дата", "Время", "Имя файла", "Путь к файлу"};
    QList<QString> name_column_list_result = {"а", "б", "в", "г", "д", "е", "ё", "ж", "з", "и", "й", "к", "л", "м", "н", \
    "о", "п", "р", "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я"};
    ui->tableWidget->setHorizontalHeaderLabels(name_column_list_report);
    ui->tableWidget->setColumnWidth(0, 10);
    //for(int i = 6; i != ui->tableWidget->columnCount(); ++i)
        //ui->tableWidget->setColumnWidth(i, 15);
    ui->tableWidget->verticalHeader()->setVisible(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

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
    counter_row++;
    QTime time = QTime::currentTime();
    QString time_as_string = time.toString("hh : mm : ss");
    QDate date = QDate::currentDate();
    QString date_as_string = date.toString("dd.MM.yyyy");
    QList string = {"counter_row", "first_name", "second_name", "otchestvo", "time_as_string", "date_as_string", "filename"\
                    "file_path"};
    for(int column = 0; column != ui->tableWidget->columnCount(); column++){
        QTableWidgetItem *item = new QTableWidgetItem(string[column]);

    }

    ui->tableWidget->setItem(counter_row, 0, (new QTableWidgetItem(counter_row))->setTextAlignment(Qt::AlignCenter));
    ui->tableWidget->setItem(counter_row, 1, (new QTableWidgetItem(second_name))->setTextAlignment(Qt::AlignCenter));
    ui->tableWidget->setItem(counter_row, 2, new QTableWidgetItem(first_name).setTextAlignment(Qt::AlignCenter));
    ui->tableWidget->setItem(counter_row, 3, new QTableWidgetItem(otchestvo).setTextAlignment(Qt::AlignCenter));
    ui->tableWidget->setItem(counter_row, 4, new QTableWidgetItem(date_as_string).setTextAlignment(Qt::AlignCenter));
    ui->tableWidget->setItem(counter_row, 5, new QTableWidgetItem(time_as_string).setTextAlignment(Qt::AlignCenter));
    ui->tableWidget->setItem(counter_row, 6, new QTableWidgetItem(filename).setTextAlignment(Qt::AlignCenter));
    ui->tableWidget->setItem(counter_row, 7, new QTableWidgetItem(file_path).setTextAlignment(Qt::AlignCenter));


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

