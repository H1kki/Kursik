#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "mainwindow.h"

namespace Ui {
class loginWindow;
}

class loginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit loginWindow(QWidget *parent = nullptr);
    ~loginWindow();

signals:
    void loginwindow();

private slots:
    void on_signIn_clicked();

private:
    Ui::loginWindow *ui;
    MainWindow *mainw;
    bool checkLog();
};

#endif // LOGINWINDOW_H
