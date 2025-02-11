#ifndef REPORTWINDOW_H
#define REPORTWINDOW_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
class ReportWindow;
}

class ReportWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReportWindow(QMainWindow *parent = nullptr, const QString& second_name = "", const QString& first_name = "", \
                            const QString& otchestvo = "", const QString& ip_adress = "Связь в базой данных отсутствует", \
                            const QString& file_name = "", const std::vector<std::vector<int> > count_of_symbol = {});
    ~ReportWindow();

private slots:
    void on_pushButton_back_clicked();

signals:
    void showMainTable();

private:
    Ui::ReportWindow *ui;
    int count_letters = 0, count_paragraph = 0, count_proposal = 0, count_words = 0, count_numbers = 0, count_glasn = 0, count_soglasn = 0;

    QLabel *name_label_for_statusbar;
    QLabel *ip_label_for_statusbar;
    QLabel *file_name_label_for_statusbar;


};

#endif // REPORTWINDOW_H
