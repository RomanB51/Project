#include "reportWindow.h"
#include "ui_reportWindow.h"

reportWindow::reportWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::reportWindow)
{
    ui->setupUi(this);
}

reportWindow::~reportWindow()
{
    delete ui;
}
