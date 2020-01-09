#ifndef INSERTDATA_H
#define INSERTDATA_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QMessageBox>
#include "database.h"

namespace Ui {
class insertData;
}

class insertData : public QDialog
{
    Q_OBJECT

public:
    explicit insertData(QWidget *parent = nullptr);
    ~insertData();

signals:
    void signalReady();

private slots:
    void on_insert_clicked();

private:
    Ui::insertData *ui;
    DataBase *db;
    QSqlTableModel *model;
    QDataWidgetMapper *mapper;

private:
    void setupModel();
    void createUI();
};

#endif // INSERTDATA_H
