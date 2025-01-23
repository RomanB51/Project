#ifndef REPORTWINDOW_H
#define REPORTWINDOW_H

#include <QMainWindow>

namespace Ui {
class ReportWindow;
}

class ReportWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReportWindow(QMainWindow *parent = nullptr, const QString& second_name = "", const QString& first_name = "",\
                        const QString& otchestvo = "", std::vector<std::vector<int> > count_of_symbol = {}, const int counter_of_troitochie = 0);
    ~ReportWindow();

private slots:
    void on_pushButton_back_clicked();

signals:
    void showMainTable();

private:
    Ui::ReportWindow *ui;
    int count_letters = 0, count_paragraph = 0, count_proposal = 0, count_words = 0, count_numbers = 0, count_glasn = 0, count_soglasn = 0;


};

#endif // REPORTWINDOW_H
