#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#define APP_VERSION_NR 1

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(initDatabase())
        populateDataItem();
    else qApp->quit();

    connect(ui->deleteButton, SIGNAL(clicked(bool)),this, SLOT(remove()));
    connect(ui->addButton, SIGNAL(clicked(bool)),this, SLOT(addnew()));
    connect(ui->submitButton, SIGNAL(clicked(bool)),this, SLOT(save()));

    ui->edIsbn->setText("123456789");
    ui->edTitle->setText("Qt Test Sql Apllication");
    ui->edEdition->setText("2019");
    ui->edPublisher->setText("Türkay Biliyor");
    ui->edCopyright->setText("By Türkay Biliyor");
    ui->dspinPrice->setValue(3.25);
    ui->edAuthors->setText("Türkay Biliyor");
}

MainWindow::~MainWindow()
{
    closeDatabase();
    delete model;
    delete ui;
}

void MainWindow::populateDataItem(){

    model = new QSqlTableModel(this, db);
    model->setTable("books");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("ISBN"));
    model->setHeaderData(2, Qt::Horizontal, tr("Title"));
    model->setHeaderData(3, Qt::Horizontal, tr("Edition"));
    model->setHeaderData(4, Qt::Horizontal, tr("Publisher"));
    model->setHeaderData(5, Qt::Horizontal, tr("Copyright"));
    model->setHeaderData(6, Qt::Horizontal, tr("Price"));
    model->setHeaderData(7, Qt::Horizontal, tr("Authors"));

    ui->tableView->setModel(model);
    ui->tableView->setAlternatingRowColors(true);
}

bool MainWindow::initDatabase(){

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName(QDir::currentPath() + "/testDB.db");
    db.setUserName("root");
    db.setPassword("root");

    qDebug() << db.database().databaseName();

    if(!db.open())
    {
        QMessageBox::information(this, "Error", "Couldn't open database!");
        return false;
    }

    QSqlQuery qry(db);

    /*QSqlQuery query;
    QString tableName = "books";
    QString sqlQuery = QString("SELECT name FROM sqlite_master WHERE type =:table AND name = '%1' ").arg(tableName);
    query.prepare(sqlQuery);
    query.bindValue(":table", "table");
    query.exec();
    int fieldNo = query.record().indexOf("name");
    while (query.next()) {
        QString _name = query.value(fieldNo).toString();
        qDebug() << "Table Name" << _name ;
    }*/

    // Drop table books
    /*qry.prepare( "DROP TABLE IF EXISTS books" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
        qDebug() << "books drop query executed successfully.!";*/

    // Creating table books
    qry.prepare( "CREATE TABLE IF NOT EXISTS books (ID INTEGER PRIMARY KEY AUTOINCREMENT DEFAULT 1, ISBN VARCHAR(30), Title VARCHAR(30), Edition VARCHAR(100), Publisher VARCHAR(30), Copyright VARCHAR(30), Price VARCHAR(30), Authors VARCHAR(30))" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
        qDebug() << "books create query executed successfully.";


    return true;
}

void MainWindow::closeDatabase(){
    db.close();
}

void MainWindow::addnew(){
    int row=0;
    model->insertRows(row,1);
    model->setData(model->index(row,1),NULL);
    model->setData(model->index(row,1),ui->edIsbn->text());
    model->setData(model->index(row,2),ui->edTitle->text());
    model->setData(model->index(row,3),ui->edEdition->text());
    model->setData(model->index(row,4),ui->edPublisher->text());
    model->setData(model->index(row,5),ui->edCopyright->text());
    model->setData(model->index(row,6),ui->dspinPrice->value());
    model->setData(model->index(row,7),ui->edAuthors->text());
    model->submitAll();
}

void MainWindow::remove(){
    int row = ui->tableView->currentIndex().row();
    if(QMessageBox::question(nullptr, "Delete", "Record no. "
                             +QString::number(row+1)
                             +" will be deleted. Are you sure?",
                             QMessageBox::No,QMessageBox::Yes)==
            QMessageBox::Yes){
        model->removeRow(row);
        model->submitAll();
    }
}

void MainWindow::save()
{
    bool flag = model->submitAll();
    if(flag==false)
        QMessageBox::critical(nullptr,"Failed", "cannot save changes.");
    else
        QMessageBox::information(nullptr,"success", "changes saved successfully.");
}
