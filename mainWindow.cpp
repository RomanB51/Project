﻿#include "mainWindow.h"
#include "ui_mainWindow.h"
#include "main.h"
#include "reportWindow.h"


#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QGuiApplication>
#include <map>
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <vector>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent, const QString &second_name, const QString &first_name, const QString &otchestvo)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->first_name = first_name;
    this->second_name = second_name;
    this->otchestvo = otchestvo;


    ui->tableWidget->setColumnCount(7);
    QList<QString> name_column_list_report = {"Имя файла", "Путь к файлу", "Дата", "Время", "Фамилия", "Имя", "Отчество"};
    QList<QString> name_column_list_result = {"а", "б", "в", "г", "д", "е", "ё", "ж", "з", "и", "й", "к", "л", "м", "н", \
    "о", "п", "р", "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я"};
    ui->tableWidget->setHorizontalHeaderLabels(name_column_list_report);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->installEventFilter(this);

    ui->statusbar->showMessage(this->second_name + " " + this->first_name + " " + this->otchestvo);

    password_window = parent;

}

MainWindow::~MainWindow()
{
    delete ui;
}

// std::map <QString, std::vector <QString>> stroka_of_MainWindow;
// std::map <QString, std::vector <std::vector<int>>> stroka_of_ReportWindow;
// int counter_row = 0;


// const QString rus_small_letters[33] = {"а", "б", "в", "г", "д", "е", "ё", "ж", "з", "и", "й", "к", "л", "м", "н", \
//                                  "о", "п", "р", "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я"};
// std::vector<int> count_rus_small_letters = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// const QString rus_big_letters[33] = {"А", "Б", "В", "Г", "Д", "Е", "Ё", "Ж", "З", "И", "Й", "К", "Л", "М", "Н", \
//                                "О", "П", "Р", "С", "Т", "У", "Ф", "Х", "Ц", "Ч", "Ш", "Щ", "Ъ", "Ы", "Ь", "Э", "Ю", "Я"};
// std::vector<int> count_rus_big_letters = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// const QString eng_small_letters[26] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", \
//                                  "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
// std::vector<int> count_eng_small_letters = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// const QString eng_big_letters[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", \
//                                "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
// std::vector<int> count_eng_big_letters = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// const QString numbers[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
// std::vector<int> count_numbers = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// const QString signs[28] = {"!", "?", ".", ",", "@", "#", "$", "%", "^", "&", "*", "(", ")", "-", "+", "=", "\n", "{", "}"\
//                      "[", "]", "/", "<", ">", ":", ";", "'", "'"};
// std::vector<int> count_signs = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


void MainWindow::on_pushButton_ChooseFile_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Окно выбора файлов", "D:/C++/My_project/", "Text File (*.txt)");
    //QString file_path = QFileDialog::getOpenFileName(this, "Окно выбора файлов", "/home/roman/MyProject/", "Text File (*.txt)");

    QFile file(file_path);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
    }
    else{
        counter_row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(counter_row);
        QFileInfo file_info(file_path);
        QString file_name = file_info.baseName();
        QString first_name = this->first_name;
        QString second_name = this->second_name;
        QString otchestvo = this->otchestvo;
        QString time = QTime::currentTime().toString("hh : mm : ss");
        QString date = QDate::currentDate().toString("dd.MM.yyyy");
        stroka_of_MainWindow[file_name + time] = {file_name, file_path, date, time, second_name, first_name, otchestvo};


        for(int i = 0; i != ui->tableWidget->columnCount(); i++){
            QTableWidgetItem *column = new QTableWidgetItem(stroka_of_MainWindow[file_name + time][i]);
            column->setToolTip(stroka_of_MainWindow[file_name + time][i]);
            column->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(counter_row, i, column);
        }

        QTextStream in(&file);
        QString symbol;
        QString* ptr_symbol = &symbol;

        while(in.readLineInto(ptr_symbol, 1)){
            for(size_t i = 0; i != count_rus_small_letters.size() ; ++i){
                if(*ptr_symbol == rus_small_letters[i]){
                    count_rus_small_letters[i]++;
                    break;
                }
            }
            for(size_t i = 0; i != count_rus_big_letters.size(); ++i){
                if(*ptr_symbol == rus_big_letters[i]){
                    count_rus_big_letters[i]++;
                    break;
                }
            }
            for(size_t i = 0; i != count_numbers.size(); ++i){
                if(*ptr_symbol == numbers[i]){
                    count_numbers[i]++;
                    break;
                }
            }
            for(size_t i = 0; i != count_eng_small_letters.size(); ++i){
                if(*ptr_symbol == eng_small_letters[i]){
                    count_eng_small_letters[i]++;
                    break;
                }
            }
            for(size_t i = 0; i != count_eng_big_letters.size(); ++i){
                if(*ptr_symbol == eng_big_letters[i]){
                    count_eng_big_letters[i]++;
                    break;
                }
            }
            for(size_t i = 0; i != count_signs.size(); ++i){
                if(*ptr_symbol == signs[i]){
                    count_signs[i]++;
                    break;
                }
            }
        }

        stroka_of_ReportWindow[file_name + time] = {count_rus_small_letters, count_rus_big_letters, count_numbers,\
                                                    count_eng_small_letters, count_eng_big_letters, count_signs};
        for(size_t i = 0; i != count_rus_small_letters.size(); ++i){
            qDebug() << rus_small_letters[i] << " = " << count_rus_small_letters[i] << "\t";
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

    stroka_of_MainWindow.erase(file_name_del_row + time_del_row);
    ui->tableWidget->removeRow(index_del_row);



}


QString text_of_old_item;
QString key_of_map;
int number_of_change_column;
bool MainWindow::eventFilter(QObject *obj, QEvent *evt){
    if(evt->type() == QKeyEvent::KeyRelease){
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(evt);
        if(ui->tableWidget->hasFocus() && keyEvent->key() == Qt::Key_Return){
            QTableWidgetItem *new_item = ui->tableWidget->currentItem();
            QString text_of_new_item = new_item->text();
            if(text_of_new_item != text_of_old_item && text_of_new_item != ""){
                new_item->setToolTip(text_of_new_item);
                QTableWidgetItem *column_time = ui->tableWidget->item(ui->tableWidget->currentRow(), 3);
                QString time_change_row = column_time->text();
                stroka_of_MainWindow[key_of_map][number_of_change_column] = text_of_new_item;
                auto new_key_node = stroka_of_MainWindow.extract(key_of_map);
                new_key_node.key() = text_of_new_item + time_change_row;
                stroka_of_MainWindow.insert(std::move(new_key_node));
            }
            else{
                new_item->setText(text_of_old_item);
            }
        }
    }
    return QMainWindow::eventFilter(obj, evt);
}


void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    QTableWidgetItem *column_file_name = ui->tableWidget->item(ui->tableWidget->currentRow(), 0);
    QTableWidgetItem *column_time = ui->tableWidget->item(ui->tableWidget->currentRow(), 3);
    QString file_name_change_row = column_file_name->text();
    QString time_change_row = column_time->text();
    number_of_change_column = ui->tableWidget->currentColumn();
    key_of_map = file_name_change_row + time_change_row;
    QTableWidgetItem *new_item = ui->tableWidget->currentItem();
    text_of_old_item = new_item->text();
}


void MainWindow::on_pushButton_Change_user_clicked()
{
    password_window->show();
    this->~MainWindow();
}



void MainWindow::on_pushButton_Report_clicked()
{
    if(ui->tableWidget->currentItem() != nullptr){
        QTableWidgetItem *column_file_name = ui->tableWidget->item(ui->tableWidget->currentRow(), 0);
        QTableWidgetItem *column_time = ui->tableWidget->item(ui->tableWidget->currentRow(), 3);
        QString file_name_row = column_file_name->text();
        QString time_row = column_time->text();
        reportWindow = new ReportWindow(this, this->second_name, this->first_name, this->otchestvo, stroka_of_ReportWindow[file_name_row + time_row]);
        this->hide();
        reportWindow->show();
    }
    else{
        QMessageBox::warning(this, "Ошибка", "Ты не выбрал строку");
    }

}

