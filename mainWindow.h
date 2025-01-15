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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_ChooseFile_clicked();


    void on_pushButton_Close_clicked();

    void on_pushButton_Delete_str_clicked();

    bool eventFilter(QObject *obj, QEvent *evt );

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
