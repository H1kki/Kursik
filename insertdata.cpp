#include "insertdata.h"
#include "ui_insertdata.h"

insertData::insertData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::insertData)
{
    ui->setupUi(this);
    db = new DataBase();
}

insertData::~insertData()
{
    delete ui;
}

void insertData::on_insert_clicked()
{
    /*QVariantList data;
    data.append(ui->nameLine->text());
    data.append(ui->countLine->text());
    data.append(ui->priceLine->text());
    data.append(QDate::currentDate());
    db->inserIntoTable(data);*/


    /* SQL-запрос для проверки существования записи
         * с такими же учетными данными.
         * Если запись не существует или находится лишь индекс
         * редактируемой в данный момент записи,
         * то диалог позволяет вставку записи в таблицу данных
         * */
        QSqlQuery query;
        QString str = QString("SELECT EXISTS (SELECT " TABLE_NAME " FROM " TABLE
                              " WHERE ( " TABLE_NAME " = '%1' "
                              " AND id NOT LIKE '%3' )")
                .arg(ui->nameLine->text(),
                     model->data(model->index(mapper->currentIndex(),0), Qt::DisplayRole).toString());

        query.prepare(str);
        query.exec();
        query.next();

        /* Если запись существует, то диалог вызывает
         * предупредительное сообщение
         * */
        if(query.value(0) != 0){
            QMessageBox::information(this, trUtf8("Ошибка хоста"),
                                     trUtf8("Хост с таким именем или IP-адресом уже существует"));
        /* В противном случае производится вставка новых данных в таблицу
         * и диалог завершается с передачей сигнала для обновления
         * таблицы в главном окне
         * */
        } else {
            mapper->submit();
            model->submitAll();
            emit insertWindow();
            this->close();
        }
}

void insertData::setupModel()
{
    /* Инициализируем модель и делаем выборку из неё
         * */
        model = new QSqlTableModel(this);
        model->setTable(TABLE);
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();

        /* Инициализируем mapper и привязываем
         * поля данных к объектам LineEdit
         * */
        mapper = new QDataWidgetMapper();
        mapper->setModel(model);
        mapper->addMapping(ui->nameLine, 1);
        mapper->addMapping(ui->countLine, 2);
        mapper->addMapping(ui->priceLine, 3);
        /* Ручное подтверждение изменения данных
         * через mapper
         * */
        mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

        /* Подключаем коннекты от кнопок пролистывания
         * к прилистыванию модели данных в mapper
         * */
        //connect(ui->previousButton, SIGNAL(clicked()), mapper, SLOT(toPrevious()));
        //connect(ui->nextButton, SIGNAL(clicked()), mapper, SLOT(toNext()));
        /* При изменении индекса в mapper изменяем состояние кнопок
         * */
        connect(mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtons(int)));
}

void insertData::createUI()
{

}
