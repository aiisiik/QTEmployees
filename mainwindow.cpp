#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./../../db/Employees.db");
    if (db.open()){
        ui->statusbar->showMessage("DB connected successfuly: "+db.databaseName());
        //link model to table in form
        model = new QSqlTableModel(this,db);
        model->setTable("USERS");
        model->select();
        model->setHeaderData(1,Qt::Horizontal,"Family name",Qt::DisplayRole);
        model->setHeaderData(2,Qt::Horizontal,"Given name",Qt::DisplayRole);
        model->setHeaderData(3,Qt::Horizontal,"Birthday",Qt::DisplayRole);
        model->setHeaderData(4,Qt::Horizontal,"Department",Qt::DisplayRole);
        ui->tableView->setModel(model);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableView->setColumnHidden(0, true); //hide id column
        //enable buttons
        ui->btnAdd->setEnabled(true);
        ui->btnDelete->setEnabled(true);
    }
    else{
        ui->statusbar->showMessage("DB error! "+db.lastError().databaseText());
    }
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

void MainWindow::on_btnAdd_clicked()
{
    model->insertRow(model->rowCount());
}


void MainWindow::on_btnDelete_clicked()
{
    model->removeRow(currentRow);
    model->select();
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    currentRow = index.row();

}


void MainWindow::on_btnRefresh_clicked()
{
    model->select();
}




