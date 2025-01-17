#ifndef REPORTWINDOW_H
#define REPORTWINDOW_H

#include <QMainWindow>

namespace Ui {
class reportWindow;
}

class reportWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit reportWindow(QWidget *parent = nullptr);
    ~reportWindow();

private:
    Ui::reportWindow *ui;
};

#endif // REPORTWINDOW_H
