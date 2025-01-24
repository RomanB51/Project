#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "reportWindow.h"

#include <QMainWindow>
#include <QStatusBar>
#include <QEvent>
#include <qtablewidget.h>
#include <QLabel>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, const QString& second_name = "", const QString& first_name = "",\
                        const QString& otchestvo = "", const QString ip_adress = "Связь с базой данных не установлена",\
                        const bool flag_admin_user = 0);
    ~MainWindow();

    static QString Read_rus_small_letters(int num_val);
    static QString Read_eng_small_letters(int num_val);
    static QString Read_numbers(int num_val);
    static QString Read_signs(int num_val);


private slots:

    void on_pushButton_ChooseFile_clicked();

    void on_pushButton_Close_clicked();

    void on_pushButton_Delete_str_clicked();

    bool eventFilter(QObject *obj, QEvent *evt);

    void on_tableWidget_cellDoubleClicked(int row, int column);

    void on_pushButton_Change_user_clicked();

    void on_pushButton_Report_clicked();

    void on_pushButton_day_night_theme_clicked();

signals:
    void showPasswordWindow();

public slots:
    void ShowMyself();

private:
    Ui::MainWindow *ui;

    QString first_name;
    QString second_name;
    QString otchestvo;
    QString ip_adress;

    bool shine_dark_mode = 0;
    bool flag_admin_user;

    ReportWindow *reportWindow;

    std::map <QString, std::vector <std::vector<int>>> stroka_of_ReportWindow;
    std::map <QString, std::vector <QString>> stroka_of_MainWindow;

    QList<QString> column_name_mainWindow = {"Имя файла", "Путь к файлу", "Дата", "Время", "Фамилия", "Имя", "Отчество"};

    int counter_row = 0;
    int counter_of_troitochie = 0;


    static const QString rus_small_letters[33];
    std::vector<int> count_rus_small_letters = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    const QString rus_big_letters[33] = {"А", "Б", "В", "Г", "Д", "Е", "Ё", "Ж", "З", "И", "Й", "К", "Л", "М", "Н", \
                                         "О", "П", "Р", "С", "Т", "У", "Ф", "Х", "Ц", "Ч", "Ш", "Щ", "Ъ", "Ы", "Ь", "Э", "Ю", "Я"};
    std::vector<int> count_rus_big_letters = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    static const QString eng_small_letters[26];
    std::vector<int> count_eng_small_letters = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    const QString eng_big_letters[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", \
                                         "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    std::vector<int> count_eng_big_letters = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    static const QString numbers[10];
    std::vector<int> count_numbers = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    static const QString signs[29];
    std::vector<int> count_signs = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


    QLabel *name_label_for_statusbar;
    QLabel *ip_label_for_statusbar;
    QLabel *file_name_label_for_statusbar;
};

#endif // MAINWINDOW_H
