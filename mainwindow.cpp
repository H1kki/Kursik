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
                                   << trUtf8("Назва товару")
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

//Запис данних в базу
void MainWindow::on_insertData_clicked()
{
    insertData *initData = new insertData;
    connect(initData, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));

    initData->setWindowTitle("Ввід данних");
    initData->exec();
}

//Видалення записів з бази данних
void MainWindow::on_deleteData_clicked()
{
    ui->deleteData->setEnabled(false);
    int selectedRow = ui->tableView->currentIndex().row();
    if (selectedRow >=0)
        model->removeRow(selectedRow);
    model->submitAll();
    createUI();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    ui->deleteData->setEnabled(true);
}

//Слот для оновлення данних в таблиці
void MainWindow::slotUpdateModels()
{
    model->select();
}
