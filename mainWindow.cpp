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
#include <pqxx/pqxx>

MainWindow::MainWindow(QWidget *parent, const QString &second_name, const QString &first_name, const QString &otchestvo, \
                       const QString ip_adress, const bool flag_admin_user, const QString id_staff,\
                        pqxx::connection *conn)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);

    this->conn_for_mainwindow = conn;

    this->first_name = first_name;
    this->second_name = second_name;
    this->otchestvo = otchestvo;
    this->ip_adress = ip_adress;
    this->flag_admin_user = flag_admin_user;
    this->id_staff = id_staff;


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
    last_path = QFileDialog::getOpenFileName(this, "Окно выбора файлов", last_path, "Text File (*.txt)");

    QFile file(last_path);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
    }
    else{
        counter_row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(counter_row);
        QFileInfo file_info(last_path);
        QString file_name = file_info.baseName();
        QString date = QDate::currentDate().toString("dd.MM.yyyy");
        QString time = QTime::currentTime().toString("hh:mm:ss");
        QString second_name = this->second_name;
        QString first_name = this->first_name;
        QString otchestvo = this->otchestvo;
        QString status_in_DB = "0";
        stroka_of_MainWindow[file_name + time] = {file_name, last_path, date, time, second_name, first_name, otchestvo, status_in_DB};


        for(int i = 0; i != ui->tableWidget->columnCount(); ++i){
            QTableWidgetItem *column = new QTableWidgetItem(stroka_of_MainWindow[file_name + time][i]);
            if(!flag_admin_user)
                column->setFlags(column->flags() &= ~Qt::ItemIsEditable);
            column->setBackground(Qt::darkRed);
            column->setToolTip(stroka_of_MainWindow[file_name + time][i]);
            column->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(counter_row, i, column);
        }

        stroka_of_ReportWindow[file_name + time] = {count_rus_small_letters, count_rus_big_letters, count_signs,\
                                                    count_numbers, count_eng_small_letters, count_eng_big_letters, dop_info_about_text};
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
                                        stroka_of_ReportWindow[name_file_in_map]);

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
    pqxx::work transaction(*conn_for_mainwindow);
    for(auto& [key, info] : stroka_of_MainWindow){
        if(info[7] == "0"){
            transaction.exec("INSERT INTO report(staffer, file_name, file_path, date, time, second_name, first_name, otchestvo, rus_letters, eng_letters,"
            "numbers, symbols, troetochie, letters, paragraph, proposal, words, number, glasn, soglasn) VALUES "
            "(" + id_staff.toStdString() + ", '" + info[0].toStdString() + "', '" + info[1].toStdString() + "', to_date('" +\
            info[2].toStdString() + "', 'DD.MM.YYYY'), '" + info[3].toStdString() + "', '" + info[4].toStdString() + "', '" + info[5].toStdString() +\
            "', '" + info[6].toStdString() + "', '" + int_to_str(sum_rus_letters) + "', '" + int_to_str(sum_eng_letters) + \
            "', '" + int_to_str(stroka_of_ReportWindow[key][3]) + "', '" + int_to_str(stroka_of_ReportWindow[key][2]) + "', " + \
            std::to_string(stroka_of_ReportWindow[key][6][0]) + ", " + std::to_string(stroka_of_ReportWindow[key][6][1]) + ", " +\
            std::to_string(stroka_of_ReportWindow[key][6][2]) + ", " + std::to_string(stroka_of_ReportWindow[key][6][3]) + ", " + \
            std::to_string(stroka_of_ReportWindow[key][6][4]) + ", " + std::to_string(stroka_of_ReportWindow[key][6][5]) + ", " +\
            std::to_string(stroka_of_ReportWindow[key][6][6]) + ", " + std::to_string(stroka_of_ReportWindow[key][6][7]) + ")");
            info[7] = "1";
            qDebug() << "Загружено";
        }
    }
    transaction.commit();
    int i = 0;
    while(i != ui->tableWidget->rowCount()){
        if(ui->tableWidget->item(i, 0)->background().color() == Qt::darkRed){
            ui->tableWidget->item(i, 0)->setBackground(Qt::darkGreen);
            ui->tableWidget->item(i, 0)->setFlags(ui->tableWidget->item(i, 0)->flags() &= ~Qt::ItemIsEditable);
            ui->tableWidget->item(i, 1)->setBackground(Qt::darkGreen);
            ui->tableWidget->item(i, 1)->setFlags(ui->tableWidget->item(i, 1)->flags() &= ~Qt::ItemIsEditable);
            ui->tableWidget->item(i, 2)->setBackground(Qt::darkGreen);
            ui->tableWidget->item(i, 2)->setFlags(ui->tableWidget->item(i, 2)->flags() &= ~Qt::ItemIsEditable);
            ui->tableWidget->item(i, 3)->setBackground(Qt::darkGreen);
            ui->tableWidget->item(i, 3)->setFlags(ui->tableWidget->item(i, 3)->flags() &= ~Qt::ItemIsEditable);
            ui->tableWidget->item(i, 4)->setBackground(Qt::darkGreen);
            ui->tableWidget->item(i, 4)->setFlags(ui->tableWidget->item(i, 4)->flags() &= ~Qt::ItemIsEditable);
            ui->tableWidget->item(i, 5)->setBackground(Qt::darkGreen);
            ui->tableWidget->item(i, 5)->setFlags(ui->tableWidget->item(i, 5)->flags() &= ~Qt::ItemIsEditable);
            ui->tableWidget->item(i, 6)->setBackground(Qt::darkGreen);
            ui->tableWidget->item(i, 6)->setFlags(ui->tableWidget->item(i, 6)->flags() &= ~Qt::ItemIsEditable);
        }
        ++i;
    }
}


void MainWindow::on_pushButton_import_from_BD_clicked()
{
    filterWindow = new FilterWindow(this, filter_second_name, filter_first_name, filter_otchestvo, filter_file_name, filter_date,\
                                    filter_counter_last_report);
    filterWindow->show();
    connect(filterWindow, &FilterWindow::showDate, this, &MainWindow::ShowDateFromDB);
}

void MainWindow::ShowDateFromDB()
{
    if(filter_second_name == "" && filter_first_name == "" && filter_otchestvo == "" && filter_file_name == "" && filter_date == "" &&\
                                                                                                            filter_counter_last_report == ""){
        QMessageBox::warning(this, "Ошибка", "Выберите хотя бы один фильтр");
    }
    else{
        pqxx::work transaction(*conn_for_mainwindow);

        std::string first_part_of_request = "select file_name, file_path, date, time, second_name, first_name, otchestvo, rus_letters, eng_letters, "
                                            "numbers, symbols, troetochie, letters, paragraph, proposal, words, number, glasn, soglasn from report where";

        std::string second_part_of_request;
        second_part_of_request.reserve(100);
        if(filter_second_name != ""){
            second_part_of_request += " second_name LIKE '" + filter_second_name.toStdString() + "' and";
        }
        if(filter_first_name != ""){
            second_part_of_request += " first_name LIKE '" + filter_first_name.toStdString() + "' and";
        }
        if(filter_otchestvo != ""){
            second_part_of_request += " otchestvo LIKE '" + filter_otchestvo.toStdString() + "' and";
        }
        if(filter_file_name != ""){
            second_part_of_request += " file_name LIKE '" + filter_file_name.toStdString() + "' and";
        }
        if(filter_date != ""){
            QDate date = QDate::fromString(filter_date, "dd.MM.yyyy");
            QString qstr_date = date.toString("yyyy-MM-dd");

            second_part_of_request += " date::text LIKE '" + qstr_date.toStdString() + "' and";
        }
        second_part_of_request.erase(second_part_of_request.size() - 4);

        if(filter_counter_last_report != "0"){
             second_part_of_request += " LIMIT " + filter_counter_last_report.toStdString();
        }
        second_part_of_request.push_back(';');
        qDebug() << "Check: " << second_part_of_request << '\n';

        std::string total_request = first_part_of_request + second_part_of_request;
        qDebug() << "Check total:  " << total_request << '\n';





        pqxx::result res = transaction.exec(total_request);
        if(!res.empty()){
            for (pqxx::result::const_iterator row = res.begin(); row != res.end(); ++row){
                QString key = QString::fromStdString(row[0].as<std::string>()) + QString::fromStdString(row[3].as<std::string>());
                if(stroka_of_MainWindow.find(key) == stroka_of_MainWindow.end()){

                    stroka_of_MainWindow[key] = {QString::fromStdString(row[0].as<std::string>()), QString::fromStdString(row[1].as<std::string>()),
                                                QString::fromStdString(row[2].as<std::string>()), QString::fromStdString(row[3].as<std::string>()),
                                                QString::fromStdString(row[4].as<std::string>()), QString::fromStdString(row[5].as<std::string>()),
                                                QString::fromStdString(row[6].as<std::string>()), "1"};

                    std::vector<int> dop_info = {row[11].as<int>(), row[12].as<int>(), row[13].as<int>(), row[14].as<int>(), row[15].as<int>(),
                                                row[16].as<int>(), row[17].as<int>(), row[18].as<int>()};

                    stroka_of_ReportWindow[key] = {str_to_int(row[7].as<std::string>()), str_to_int(row[8].as<std::string>()),
                                                    str_to_int(row[9].as<std::string>()), str_to_int(row[10].as<std::string>()),
                                                    dop_info};


                    counter_row = ui->tableWidget->rowCount();
                    ui->tableWidget->insertRow(counter_row);
                    for(int i = 0; i != ui->tableWidget->columnCount(); ++i){
                        QTableWidgetItem *column = new QTableWidgetItem(stroka_of_MainWindow[key][i]);
                        column->setFlags(column->flags() &= ~Qt::ItemIsEditable);
                        column->setBackground(Qt::darkGreen);
                        column->setToolTip(stroka_of_MainWindow[key][i]);
                        column->setTextAlignment(Qt::AlignCenter);
                        ui->tableWidget->setItem(counter_row, i, column);
                    }
                }
            }
        }
        else{
            QMessageBox::warning(this, "Отчеты не найдены", "Данные с указанными фильтрами не найдены!");
        }
        transaction.commit();

        qDebug() << "Close";
    }
}


std::string MainWindow::int_to_str(std::vector<int> arr){
        return accumulate(std::next(std::begin(arr)), std::end(arr), std::to_string(arr[0]),\
                          [](std::string(a), int b){return a + "-" + std::to_string(b);});
}

std::vector<int> MainWindow::str_to_int(std::string str){
    std::string num;
    std::vector<int> vec;
    vec.reserve(33);

    for(int j = 0; j != str.size(); ++j){
        if(str[j] != '-'){
            num += str[j];
        }
        else{
            vec.push_back(std::stoi(num));
            num.clear();
        }
    }
    vec.push_back(std::stoi(num));
    return vec;
}
