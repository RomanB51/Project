#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "secondwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Entry_clicked();

    void on_pushButton_Escape_clicked();

private:
    Ui::MainWindow *ui;
    SecondWindow *secondWindow;
};
#endif // MAINWINDOW_H
