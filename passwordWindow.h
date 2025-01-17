#ifndef PASSWORDWINDOW_H
#define PASSWORDWINDOW_H

#include <QDialog>
#include <QAction>
#include "mainWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class PasswordWindow;
}
QT_END_NAMESPACE

class PasswordWindow : public QDialog
{
    Q_OBJECT

public:
    PasswordWindow(QWidget *parent = nullptr);
    ~PasswordWindow();

private slots:
    void on_pushButton_Entry_clicked();

    void on_pushButton_Escape_clicked();

    void Show_Hide_Password();

    bool eventFilter(QObject *obj, QEvent *evt);

private:
    Ui::PasswordWindow *ui;
    MainWindow *mainWindow;
    QAction *customAction;
};
#endif // PASSWORDWINDOW_H
