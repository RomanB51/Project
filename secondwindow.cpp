#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

SecondWindow::SecondWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SecondWindow)
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

SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::on_pushButton_clicked()
{
    QString filter = "Text File (*.txt)";
    QString filename = QFileDialog::getOpenFileName(this, "Окно выбора файлов", "D:/C++/", filter);
    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text)){ //Проверка на то, можем ли мы что-либо записывать
        QMessageBox::warning(this, "Title", "Не удалось открыть файл");
    }
    QTextStream in(&file);
    QString *k;
    /*int g = 0;
    while(in.readLineInto(k, 1))
        if(k == "о")
            g++;
    qDebug() << g;

    QString text = in.readAll();
    qDebug() << text;*/
    file.close();
}

