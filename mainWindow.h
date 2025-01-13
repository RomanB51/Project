#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QStatusBar>

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_ChooseFile_clicked();

private:
    Ui::MainWindow *ui;
    QStatusBar *statusbar;
};

#endif // MAINWINDOW_H
