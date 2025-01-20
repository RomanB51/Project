#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QStatusBar>
#include <QEvent>
#include "reportWindow.h"
#include <qtablewidget.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, const QString& second_name = "", const QString& first_name = "",\
                        const QString& otchestvo = "");
    ~MainWindow();

private slots:

    void on_pushButton_ChooseFile_clicked();

    void on_pushButton_Close_clicked();

    void on_pushButton_Delete_str_clicked();

    bool eventFilter(QObject *obj, QEvent *evt);

    void on_tableWidget_cellDoubleClicked(int row, int column);

    void on_pushButton_Change_user_clicked();

    void on_pushButton_Report_clicked();

private:
    Ui::MainWindow *ui;

    QString first_name;
    QString second_name;
    QString otchestvo;

    QWidget *password_window;
    QMainWindow *reportWindow;

    std::map <QString, std::vector <QString>> stroka_of_MainWindow;
    std::map <QString, std::vector <std::vector<int>>> stroka_of_ReportWindow;
    int counter_row = 0;


    const QString rus_small_letters[33] = {"а", "б", "в", "г", "д", "е", "ё", "ж", "з", "и", "й", "к", "л", "м", "н", \
                                           "о", "п", "р", "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я"};
    std::vector<int> count_rus_small_letters = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    const QString rus_big_letters[33] = {"А", "Б", "В", "Г", "Д", "Е", "Ё", "Ж", "З", "И", "Й", "К", "Л", "М", "Н", \
                                         "О", "П", "Р", "С", "Т", "У", "Ф", "Х", "Ц", "Ч", "Ш", "Щ", "Ъ", "Ы", "Ь", "Э", "Ю", "Я"};
    std::vector<int> count_rus_big_letters = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    const QString eng_small_letters[26] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", \
                                           "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    std::vector<int> count_eng_small_letters = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    const QString eng_big_letters[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", \
                                         "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    std::vector<int> count_eng_big_letters = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    const QString numbers[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    std::vector<int> count_numbers = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    const QString signs[28] = {"!", "?", ".", ",", "@", "#", "$", "%", "^", "&", "*", "(", ")", "-", "+", "=", "\n", "{", "}"\
                               "[", "]", "/", "<", ">", ":", ";", "'", "'"};
    std::vector<int> count_signs = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
};

#endif // MAINWINDOW_H
