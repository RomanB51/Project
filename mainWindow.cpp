#include "mainWindow.h"
#include "ui_mainWindow.h"

#include "reportWindow.h"


#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>
#include <QGuiApplication>
#include <map>
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <vector>

MainWindow::MainWindow(QWidget *parent, const QString &second_name, const QString &first_name, const QString &otchestvo, \
                       const QString ip_adress, const bool flag_admin_user)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);

    this->first_name = first_name;
    this->second_name = second_name;
    this->otchestvo = otchestvo;
    this->ip_adress = ip_adress;
    this->flag_admin_user = flag_admin_user;


    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels(column_name_mainWindow);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->installEventFilter(this);

    name_label_for_statusbar = new QLabel(this->second_name + " " + this->first_name + " " + this->otchestvo, this);
    ip_label_for_statusbar = new QLabel(this->ip_adress, this);
    file_name_label_for_statusbar = new QLabel("", this);
    ui->statusbar->addPermanentWidget(name_label_for_statusbar, 1);
    ui->statusbar->addPermanentWidget(ip_label_for_statusbar, 1);
    ui->statusbar->addPermanentWidget(file_name_label_for_statusbar, 1);

    ui->pushButton_day_night_theme->setIcon(QIcon(":/Images/Icons/Dark.png"));

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

QString MainWindow::Read_rus_small_letters(int num_val){return rus_small_letters[num_val];}

QString MainWindow::Read_eng_small_letters(int num_val){return eng_small_letters[num_val];}

QString MainWindow::Read_numbers(int num_val){return numbers[num_val];}

QString MainWindow::Read_signs(int num_val){return signs[num_val];}


QString MainWindow::filter_second_name = "";

QString MainWindow::filter_first_name = "";

QString MainWindow::filter_otchestvo = "";

QString MainWindow::filter_file_name = "";

QString MainWindow::filter_date = "";

QString MainWindow::filter_counter_last_report = "";

void MainWindow::set_filter_second_name(QString newVal){filter_second_name = newVal;}

void MainWindow::set_filter_first_name(QString newVal){filter_first_name = newVal;}

void MainWindow::set_filter_otchestvo(QString newVal){filter_otchestvo = newVal;}

void MainWindow::set_filter_file_name(QString newVal){filter_file_name = newVal;}

void MainWindow::set_filter_date(QString newVal){filter_date = newVal;}

void MainWindow::set_filter_counter_last_report(QString newVal){filter_counter_last_report = newVal;}





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
        QString date = QDate::currentDate().toString("dd.MM.yyyy");
        QString time = QTime::currentTime().toString("hh : mm : ss");
        QString second_name = this->second_name;
        QString first_name = this->first_name;
        QString otchestvo = this->otchestvo;
        QString status_in_DB = "0";
        stroka_of_MainWindow[file_name + time] = {file_name, file_path, date, time, second_name, first_name, otchestvo, status_in_DB};


        for(int i = 0; i != ui->tableWidget->columnCount(); i++){
            QTableWidgetItem *column = new QTableWidgetItem(stroka_of_MainWindow[file_name + time][i]);
            if(!flag_admin_user)
                column->setFlags(column->flags() &= ~Qt::ItemIsEditable);
            column->setBackground(Qt::red);
            column->setToolTip(stroka_of_MainWindow[file_name + time][i]);
            column->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(counter_row, i, column);
        }

        stroka_of_ReportWindow[file_name + time] = {count_rus_small_letters, count_rus_big_letters, count_signs,\
                                                    count_numbers, count_eng_small_letters, count_eng_big_letters};
        func_counter_symbol(file, file_name + time);

        file.close();
    }
}



void MainWindow::on_pushButton_Close_clicked()
{
    qApp->quit();
}



void MainWindow::on_pushButton_Delete_str_clicked()
{
    int index_del_row = ui->tableWidget->currentRow();
    QTableWidgetItem *column_file_name = ui->tableWidget->item(index_del_row, 0);
    QTableWidgetItem *column_time = ui->tableWidget->item(index_del_row, 3);
    QString file_name_del_row = column_file_name->text();
    QString time_del_row = column_time->text();

    ui->tableWidget->removeRow(index_del_row);
    stroka_of_MainWindow.erase(file_name_del_row + time_del_row);
    stroka_of_ReportWindow.erase(file_name_del_row + time_del_row);

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
                stroka_of_MainWindow[key_of_map][number_of_change_column] = text_of_new_item;

                QTableWidgetItem *column_time = ui->tableWidget->item(ui->tableWidget->currentRow(), 3);
                QString time_change_row = column_time->text();
                QTableWidgetItem *column_file_name = ui->tableWidget->item(ui->tableWidget->currentRow(), 0);
                QString file_name_change_row = column_file_name->text();

                auto new_key_node_stroka_of_MainWindow = stroka_of_MainWindow.extract(key_of_map);
                auto new_key_node_stroka_of_ReportWindow = stroka_of_ReportWindow.extract(key_of_map);


                new_key_node_stroka_of_MainWindow.key() = file_name_change_row + time_change_row;
                new_key_node_stroka_of_ReportWindow.key() = file_name_change_row + time_change_row;

                stroka_of_MainWindow.insert(std::move(new_key_node_stroka_of_MainWindow));
                stroka_of_ReportWindow.insert(std::move(new_key_node_stroka_of_ReportWindow));
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
    key_of_map = file_name_change_row + time_change_row;

    number_of_change_column = ui->tableWidget->currentColumn();

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

        reportWindow = new ReportWindow(this, this->second_name, this->first_name, this->otchestvo, this->ip_adress, file_name_row,\
                                        stroka_of_ReportWindow[name_file_in_map], counter_of_troitochie);

        connect(reportWindow, &ReportWindow::showMainTable, this, &MainWindow::ShowMyself);
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


void MainWindow::on_pushButton_day_night_theme_clicked()
{
    shine_dark_mode = !shine_dark_mode;
    if(shine_dark_mode){
        ui->pushButton_day_night_theme->setIcon(QIcon(":/Images/Icons/Dark.png"));
        QPalette darkPalette;

        darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::WindowText, Qt::white);
        darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
        darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::ToolTipBase, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::ToolTipText, Qt::white);
        darkPalette.setColor(QPalette::Text, Qt::white);
        darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::ButtonText, Qt::white);

        qApp->setPalette(darkPalette);
    }
    else{
        ui->pushButton_day_night_theme->setIcon(QIcon(":/Images/Icons/Shine.png"));
        qApp->setPalette(style()->standardPalette());
    }
}




void MainWindow::on_pushButton_export_to_BD_clicked()
{
    for(const auto& [key, info] : stroka_of_MainWindow){
        if(info[7] == "0"){
            qDebug() << info[0] + info[3];
        }
    }
}


void MainWindow::on_pushButton_import_from_BD_clicked()
{
    filterWindow = new FilterWindow(this, filter_second_name, filter_first_name, filter_otchestvo, filter_file_name, filter_date,\
                                    filter_counter_last_report);
    filterWindow->show();
}

