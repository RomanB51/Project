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

    void on_pushButton_Exit_clicked();

    void Show_Hide_Password();

    bool eventFilter(QObject *obj, QEvent *evt);

public slots:
    void ShowMe();

private:
    Ui::PasswordWindow *ui;
    MainWindow *mainWindow;
    QAction *customAction;


    bool flag_for_focus_enter_after_QMessage = 1;
    bool flag_for_show_hide_password = 1;
    bool flag_admin_user = 0;
};
#endif // PASSWORDWINDOW_H
