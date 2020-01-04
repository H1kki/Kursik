#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = new DataBase();
    db->connectToDataBase();

    this->setupModel(TABLE,
                     QStringList() << trUtf8("id")
                                   << trUtf8("Ім'я")
                                   << trUtf8("Кількість")
                                   << trUtf8("Ціна")
                                   << trUtf8("Дата добавлення")
               );

    this->createUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    model = new QSqlTableModel(this);
    model->setTable(tableName);

    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    model->setSort(0,Qt::AscendingOrder);
}

void MainWindow::createUI()
{
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    model->select();
}

void MainWindow::on_pushButton_clicked()
{
    QVariantList data;
    data.append(ui->lineEdit->text());
    data.append(ui->lineEdit_2->text());
    data.append(ui->lineEdit_3->text());
    data.append(QDate::currentDate());
    db->inserIntoTable(data);
    createUI();

}

void MainWindow::on_pushButton_2_clicked()
{
    //int id = ui->tableView->currentIndex().row();
    //id+=1;
    //QString name = ui->tableView->model()->columnCount();
    //db->deleteData(id);
    //int rowCount = ui->tableView->model()->rowCount();
    //for (int i = id;i<=rowCount;i++) {
    //    db->update(i);
    //}
    ui->pushButton_2->setEnabled(false);
    int selectedRow = ui->tableView->currentIndex().row();
    if (selectedRow >=0)
        model->removeRow(selectedRow);
    model->submitAll();
    createUI();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    ui->pushButton_2->setEnabled(true);
}
