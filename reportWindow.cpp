#include "reportWindow.h"
#include "ui_reportWindow.h"

#include "mainWindow.h"

ReportWindow::ReportWindow(QMainWindow *parent, const QString &second_name, const QString &first_name, const QString &otchestvo, \
                           const QString& ip_adress, const QString& file_name, const std::vector<std::vector<int>> count_of_symbol,
                           const int counter_of_troitochie)
    : QMainWindow(parent)
    , ui(new Ui::ReportWindow)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);

    name_label_for_statusbar = new QLabel(second_name + " " + first_name + " " + otchestvo, this);
    ip_label_for_statusbar = new QLabel(ip_adress, this);
    file_name_label_for_statusbar = new QLabel(file_name, this);
    file_name_label_for_statusbar->setAlignment(Qt::AlignRight);
    ui->statusbar->addPermanentWidget(name_label_for_statusbar, 1);
    ui->statusbar->addPermanentWidget(ip_label_for_statusbar, 1);
    ui->statusbar->addPermanentWidget(file_name_label_for_statusbar, 1);

    ui->tableWidget_russian->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_english->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_symbol->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_number->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget_russian->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_english->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_symbol->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_number->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tabWidget->setCurrentIndex(0);

    count_paragraph = count_of_symbol[2][27];
    count_words = count_of_symbol[2][28] + 1;
    count_proposal = counter_of_troitochie + count_of_symbol[2][0] + count_of_symbol[2][1] + count_of_symbol[2][2];

    for(int i = 0; i != 33; ++i){
        if(i == 0 || i == 5 || i == 6 || i == 9 || i == 15 || i == 20 || i == 28 || i == 30 || i == 31 || i == 32)
            count_glasn += count_of_symbol[0][i] + count_of_symbol[1][i];
        else
            count_soglasn += count_of_symbol[0][i] + count_of_symbol[1][i];
    }
    for(int i = 0; i != 26; ++i){
        if(i == 0 || i == 4 || i == 8 || i == 14 || i == 20 || i == 24)
            count_glasn += count_of_symbol[4][i] + count_of_symbol[5][i];
        else
            count_soglasn += count_of_symbol[4][i] + count_of_symbol[5][i];
    }

    for(int i = 0; i != ui->tableWidget_russian->rowCount(); ++i){
        for(int j = 0; j != ui->tableWidget_russian->columnCount(); ++j){
            QTableWidgetItem *item = new QTableWidgetItem(MainWindow::Read_rus_small_letters(j+i*11) + " = " +\
                                                        QString::number(count_of_symbol[0][j+i*11] + count_of_symbol[1][j+i*11]));
            count_letters += count_of_symbol[0][j+i*11] + count_of_symbol[1][j+i*11];
            item->setToolTip(item->text());
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(item->flags() &= ~Qt::ItemIsEditable);
            ui->tableWidget_russian->setItem(i, j, item);
        }
    }

    for(int i = 0; i != 2; ++i){
        for(int j = 0; j != ui->tableWidget_english->columnCount(); ++j){
            QTableWidgetItem *item = new QTableWidgetItem(MainWindow::Read_eng_small_letters(j+i*9) + " = " +\
                                                          QString::number(count_of_symbol[4][j+i*9] + count_of_symbol[5][j+i*9]));
            count_letters += count_of_symbol[4][j+i*9] + count_of_symbol[5][j+i*9];
            item->setToolTip(item->text());
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(item->flags() &= ~Qt::ItemIsEditable);
            ui->tableWidget_english->setItem(i, j, item);
        }
    }

    for(int i = 2, j = 0; j != 8; ++j){
        QTableWidgetItem *item = new QTableWidgetItem(MainWindow::Read_eng_small_letters(j+i*9) + " = " +\
                                                      QString::number(count_of_symbol[4][j+i*9] + count_of_symbol[5][j+i*9]));
        count_letters += count_of_symbol[4][j+i*9] + count_of_symbol[5][j+i*9];
        item->setToolTip(item->text());
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(item->flags() &= ~Qt::ItemIsEditable);
        ui->tableWidget_english->setItem(i, j, item);
    }

    for(int i = 0; i != ui->tableWidget_number->columnCount(); ++i){
        QTableWidgetItem *item = new QTableWidgetItem("'" + MainWindow::Read_numbers(i) + "'" + " = " +\
                                                      QString::number(count_of_symbol[3][i]));
        count_numbers += count_of_symbol[3][i];
        item->setToolTip(item->text());
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(item->flags() &= ~Qt::ItemIsEditable);
        ui->tableWidget_number->setItem(0, i, item);
    }

    for(int i = 0; i != ui->tableWidget_symbol->rowCount(); ++i){
        for(int j = 0; j != ui->tableWidget_symbol->columnCount(); ++j){
            QTableWidgetItem *item = new QTableWidgetItem("'" + MainWindow::Read_signs(j+i*9) + "'" + " = " +\
                                                          QString::number(count_of_symbol[2][j+i*9]));
            item->setToolTip(item->text());
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(item->flags() &= ~Qt::ItemIsEditable);
            ui->tableWidget_symbol->setItem(i, j, item);
        }
    }

    ui->lineEdit_letters->setText(QString::number(count_letters));
    ui->lineEdit_paragraph->setText(QString::number(count_paragraph));
    ui->lineEdit_proposal->setText(QString::number(count_proposal));
    ui->lineEdit_word->setText(QString::number(count_words));
    ui->lineEdit_number->setText(QString::number(count_numbers));
    ui->lineEdit_glasn_soglasn->setText(QString::number(count_glasn) + "/" + QString::number(count_soglasn));

    qDebug() << "Окно отчета создано";

}

ReportWindow::~ReportWindow()
{
    qDebug() << "Окно букв уничтожено";
    delete ui;
}

void ReportWindow::on_pushButton_back_clicked()
{
    this->close();
}

