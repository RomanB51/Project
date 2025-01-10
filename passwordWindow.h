#ifndef PASSWORDWINDOW_H
#define PASSWORDWINDOW_H

#include <QMainWindow>
#include "mainWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class PasswordWindow;
}
QT_END_NAMESPACE

class PasswordWindow : public QMainWindow
{
    Q_OBJECT

public:
    PasswordWindow(QWidget *parent = nullptr);
    ~PasswordWindow();

private slots:
    void on_pushButton_Entry_clicked();

    void on_pushButton_Escape_clicked();

private:
    Ui::PasswordWindow *ui;
    MainWindow *mainWindow;
};
#endif // PASSWORDWINDOW_H
