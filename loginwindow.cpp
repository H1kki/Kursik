#include "loginwindow.h"
#include "ui_loginwindow.h"

loginWindow::loginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginWindow)
{
    ui->setupUi(this);
    mainw = new MainWindow;
    connect(mainw, &MainWindow::mainwindow, this, &loginWindow::show);
}

loginWindow::~loginWindow()
{
    delete ui;

}

bool loginWindow::checkLog()
{
    if(ui->pass->text() == "admin" && ui->login->text() == "admin")
        return true;
    else
    {
        QMessageBox::about(this,"PIZDA","КТО ПРОЧИТАЛ ТОТ ЗАЙЧИК");
        return false;
    }
}

void loginWindow::on_signIn_clicked()
{
    if(checkLog()){
        mainw->show();
        this->close();
    }
}
