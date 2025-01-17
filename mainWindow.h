#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QStatusBar>
#include <QEvent>
#include <qtablewidget.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, QString second_name = "", QString first_name = "",\
                        QString otchestvo = "");
    ~MainWindow();

private slots:

    void on_pushButton_ChooseFile_clicked();

    void on_pushButton_Close_clicked();

    void on_pushButton_Delete_str_clicked();

    bool eventFilter(QObject *obj, QEvent *evt);

    void on_tableWidget_cellDoubleClicked(int row, int column);

    QString getFirst_name(){ return first_name; }

    QString getSecond_name(){ return second_name; }

    QString getOtchestvo(){ return otchestvo; }


    void on_pushButton_Change_user_clicked();

private:
    Ui::MainWindow *ui;

    QString first_name;
    QString second_name;
    QString otchestvo;
};

#endif // MAINWINDOW_H
