#include "reportWindow.h"
#include "ui_reportWindow.h"

ReportWindow::ReportWindow(QMainWindow *parent, const QString &second_name, const QString &first_name, const QString &otchestvo, \
                           std::vector<std::vector<int>> count_of_symbol)
    : QMainWindow(parent)
    , ui(new Ui::ReportWindow)
{
    ui->setupUi(this);

    mainWindow = parent;

    ui->statusbar->showMessage(second_name + " " + first_name + " " + otchestvo);

    ui->tableWidget_russian->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_english->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_symbol->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_number->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget_russian->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_english->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_symbol->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_number->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for(int i = 0; i != ui->tableWidget_russian->rowCount(); ++i){
        for(int j = 0; j != ui->tableWidget_russian->columnCount(); ++j){
            QTableWidgetItem *item = new QTableWidgetItem(MainWindow::Read_rus_small_letters(j+i*11) + " = " +\
                                                        QString::number(count_of_symbol[0][j+i*11] + count_of_symbol[1][j+i*11]));
            item->setToolTip(item->text());
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(item->flags() &= ~Qt::ItemIsEditable);
            ui->tableWidget_russian->setItem(i, j, item);
        }
    }

    for(int i = 0; i != 2; ++i){
        for(int j = 0; j != ui->tableWidget_english->columnCount(); ++j){
            QTableWidgetItem *item = new QTableWidgetItem(MainWindow::Read_eng_small_letters(j+i*9) + " = " +\
                                                          QString::number(count_of_symbol[2][j+i*9] + count_of_symbol[3][j+i*9]));
            item->setToolTip(item->text());
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(item->flags() &= ~Qt::ItemIsEditable);
            ui->tableWidget_english->setItem(i, j, item);
        }
    }

    for(int i = 2, j = 0; j != 8; ++j){
        QTableWidgetItem *item = new QTableWidgetItem(MainWindow::Read_eng_small_letters(j+i*9) + " = " +\
                                                      QString::number(count_of_symbol[2][j+i*9] + count_of_symbol[3][j+i*9]));
        item->setToolTip(item->text());
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(item->flags() &= ~Qt::ItemIsEditable);
        ui->tableWidget_english->setItem(i, j, item);
    }

    for(int i = 0; i != ui->tableWidget_number->columnCount(); ++i){
        QTableWidgetItem *item = new QTableWidgetItem("'" + MainWindow::Read_numbers(i) + "'" + " = " +\
                                                      QString::number(count_of_symbol[4][i]));
        item->setToolTip(item->text());
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(item->flags() &= ~Qt::ItemIsEditable);
        ui->tableWidget_number->setItem(0, i, item);
    }

    for(int i = 0; i != ui->tableWidget_symbol->rowCount(); ++i){
        for(int j = 0; j != ui->tableWidget_symbol->columnCount(); ++j){
            QTableWidgetItem *item = new QTableWidgetItem("'" + MainWindow::Read_signs(j+i*9) + "'" + " = " +\
                                                          QString::number(count_of_symbol[5][j+i*9]));
            item->setToolTip(item->text());
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(item->flags() &= ~Qt::ItemIsEditable);
            ui->tableWidget_symbol->setItem(i, j, item);
        }
    }

}

ReportWindow::~ReportWindow()
{
    delete ui;
}

void ReportWindow::on_pushButton_back_clicked()
{
    this->~ReportWindow();
    mainWindow->show();
}

