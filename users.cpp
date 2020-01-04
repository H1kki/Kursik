#include "users.h"
#include "ui_users.h"

users::users(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::users)
{
    ui->setupUi(this);
    login = new loginWindow;
    connect(login, &loginWindow::loginwindow, this, &users::show);
}

users::~users()
{
    delete ui;
}

void users::on_adminButton_clicked()
{
    login->show();
    this->close();
}

void users::on_userButton_clicked()
{

}
