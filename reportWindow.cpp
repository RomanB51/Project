#include "./reportWindow.h"
#include "./ui_reportWindow.h"

ReportWindow::ReportWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ReportWindow)
{
    ui->setupUi(this);
}

ReportWindow::~ReportWindow()
{
    delete ui;
}
