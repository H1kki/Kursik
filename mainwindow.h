#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlTableModel>
#include "database.h"
#include "insertdata.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_insertData_clicked();

    void on_deleteData_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void slotUpdateModels();


private:
    Ui::MainWindow  *ui;
    DataBase        *db;
    QSqlTableModel  *model;
    insertData *ins;

private:
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();
};

#endif // MAINWINDOW_H
