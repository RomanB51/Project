#ifndef FILTERWINDOW_H
#define FILTERWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QDate>

namespace Ui {
class FilterWindow;
}

class FilterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FilterWindow(QWidget *parent = nullptr, QString second_name = "", QString first_name = "", QString otchestvo = "",\
                            QString file_name = "", QString date = "", QString counter_last_report = "");
    ~FilterWindow();

signals:
    void showDate();

private slots:
    void on_pushButton_Find_reports_clicked();

    void on_pushButton_Cancel_clicked();

    void on_pushButton_CleanAll_clicked();

    bool eventFilter(QObject *obj, QEvent *evt);

private:
    Ui::FilterWindow *ui;
};

#endif // FILTERWINDOW_H
