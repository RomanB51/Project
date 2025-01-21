#ifndef REPORTWINDOW_H
#define REPORTWINDOW_H

#include <QMainWindow>
#include "mainWindow.h"

namespace Ui {
class ReportWindow;
}

class ReportWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReportWindow(QMainWindow *parent = nullptr, const QString& second_name = "", const QString& first_name = "",\
                        const QString& otchestvo = "", std::vector<std::vector<int> > count_of_symbol = {});
    ~ReportWindow();

private slots:
    void on_pushButton_back_clicked();

private:
    Ui::ReportWindow *ui;
    QMainWindow *mainWindow;


};

#endif // REPORTWINDOW_H
