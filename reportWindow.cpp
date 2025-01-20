#include "reportWindow.h"
#include "ui_reportWindow.h"

ReportWindow::ReportWindow(QMainWindow *parent, const QString &second_name, const QString &first_name, const QString &otchestvo, \
                           const std::vector<std::vector<int> > &count_of_symbol)
    : QMainWindow(parent)
    , ui(new Ui::ReportWindow)
{
    ui->setupUi(this);
    qDebug() << "reportWindow make";

    this->report_count_of_symbol = count_of_symbol;
    report_count_of_symbol[0][0]++;

    mainWindow = parent;

    this->second_name = second_name;
    this->first_name = first_name;
    this->otchestvo = otchestvo;
    ui->statusbar->showMessage(this->second_name + " " + this->first_name + " " + this->otchestvo);

    ui->tableWidget_russian->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_english->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_symbol->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget_russian->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_english->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_symbol->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget_russian->installEventFilter(this);
    ui->tableWidget_english->installEventFilter(this);
    ui->tableWidget_symbol->installEventFilter(this);

}

ReportWindow::~ReportWindow()
{
    qDebug() << "reportWindow delete";
    delete ui;
}

void ReportWindow::on_pushButton_back_clicked()
{
    this->~ReportWindow();
    mainWindow->show();
}

