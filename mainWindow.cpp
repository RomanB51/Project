#include "mainWindow.h"
#include "ui_mainWindow.h"

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

    this->setAttribute(Qt::WA_DeleteOnClose);

    this->first_name = first_name;
    this->second_name = second_name;
    this->otchestvo = otchestvo;


    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels(column_name_mainWindow);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->installEventFilter(this);

    ui->statusbar->showMessage(this->second_name + " " + this->first_name + " " + this->otchestvo);

    qDebug() << "Главное окно создано";

}

MainWindow::~MainWindow()
{
    qDebug() << "Главное окно уничтожено";
    delete ui;
}

const QString MainWindow::rus_small_letters[33] = {"а", "б", "в", "г", "д", "е", "ё", "ж", "з", "и", "й", "к", "л", "м", "н", \
                                             "о", "п", "р", "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я"};

const QString MainWindow::eng_small_letters[26] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", \
                                             "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};

const QString MainWindow::numbers[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

const QString MainWindow::signs[29] = {"!", "?", ".", ",", "@", "#", "$", "%", "^", "&", "*", "(", ")", "-", "+", "=",
                                        "{", "}", "[", "]", "|", "/", "<", ">", ":", ";", "'", "\n", " "};

QString MainWindow::Read_rus_small_letters(int num_val)
{
    return rus_small_letters[num_val];
}

QString MainWindow::Read_eng_small_letters(int num_val)
{
    return eng_small_letters[num_val];
}

QString MainWindow::Read_numbers(int num_val)
{
    return numbers[num_val];
}

QString MainWindow::Read_signs(int num_val)
{
    return signs[num_val];
}



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

        int counter_of_point = 0; //служебная переменная для подсчета троеточий
        while(in.readLineInto(ptr_symbol, 1)){
            bool interrupt = 1;
            if(interrupt){
                for(size_t i = 0; i != count_rus_small_letters.size() ; ++i){
                    if(*ptr_symbol == rus_small_letters[i]){
                        count_rus_small_letters[i]++;
                        counter_of_point = 0;
                        interrupt = 0;
                        break;
                    }
                }
            }

            if(interrupt){
                for(size_t i = 0; i != count_rus_big_letters.size(); ++i){
                    if(*ptr_symbol == rus_big_letters[i]){
                        count_rus_big_letters[i]++;
                        counter_of_point = 0;
                        interrupt = 0;
                        break;
                    }
                }
            }

            if(interrupt){
                for(size_t i = 0; i != count_signs.size(); ++i){
                    if(*ptr_symbol == signs[i]){
                        count_signs[i]++;
                        interrupt = 0;
                        if(i == 2){
                            counter_of_point++;
                            if(counter_of_point == 3){
                                counter_of_troitochie++;
                                count_signs[2] -= 3;
                                counter_of_point = 0;
                            }
                        }
                        else
                            counter_of_point = 0;
                        break;
                    }
                }
            }

            if(interrupt){
                for(size_t i = 0; i != count_numbers.size(); ++i){
                    if(*ptr_symbol == numbers[i]){
                        count_numbers[i]++;
                        counter_of_point = 0;
                        interrupt = 0;
                        break;
                    }
                }
            }

            if(interrupt){
                for(size_t i = 0; i != count_eng_small_letters.size(); ++i){
                    if(*ptr_symbol == eng_small_letters[i]){
                        count_eng_small_letters[i]++;
                        counter_of_point = 0;
                        interrupt = 0;
                        break;
                    }
                }
            }

            if(interrupt){
                for(size_t i = 0; i != count_eng_big_letters.size(); ++i){
                    if(*ptr_symbol == eng_big_letters[i]){
                        count_eng_big_letters[i]++;
                        counter_of_point = 0;
                        interrupt = 0;
                        break;
                    }
                }
            }
        }


        stroka_of_ReportWindow[file_name + time] = {count_rus_small_letters, count_rus_big_letters, count_eng_small_letters,\
                                                    count_eng_big_letters, count_numbers, count_signs};

        file.close();
    }
}



void MainWindow::on_pushButton_Close_clicked()
{
    QApplication::quit();
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
    emit showPasswordWindow();
    this->close();
}



void MainWindow::on_pushButton_Report_clicked()
{
    if(ui->tableWidget->currentItem() != nullptr){
        QTableWidgetItem *column_file_name = ui->tableWidget->item(ui->tableWidget->currentRow(), 0);
        QTableWidgetItem *column_time = ui->tableWidget->item(ui->tableWidget->currentRow(), 3);
        QString file_name_row = column_file_name->text();
        QString time_row = column_time->text();
        QString name_file_in_map = file_name_row + time_row;
        reportWindow = new ReportWindow(this, this->second_name, this->first_name, this->otchestvo,\
                                        stroka_of_ReportWindow[name_file_in_map], counter_of_troitochie);
        connect(reportWindow, &ReportWindow::showMainTable, this, &MainWindow::ShowMyself);
        this->hide();
        reportWindow->show();
    }
    else{
        QMessageBox::warning(this, "Ошибка", "Выберите строку");
    }

}

void MainWindow::ShowMyself()
{
    this->show();
}

