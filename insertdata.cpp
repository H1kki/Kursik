#include "insertdata.h"
#include "ui_insertdata.h"

insertData::insertData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::insertData)
{
    ui->setupUi(this);
    db = new DataBase();

    setupModel();
}

insertData::~insertData()
{
    delete ui;
}

void insertData::on_insert_clicked()
{
    QVariantList data;
    data.append(ui->nameLine->text());
    data.append(ui->countLine->text());
    data.append(ui->priceLine->text());
    data.append(QDate::currentDate());
    db->inserIntoTable(data);
    this->close();
    ui->nameLine->clear();
    ui->countLine->clear();
    ui->priceLine->clear();
}

void insertData::setupModel()
{
        model = new QSqlTableModel(this);
        model->setTable(TABLE);
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();
}

void insertData::createUI()
{

}
