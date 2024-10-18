#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./../../../db/Employees.db");
    if (db.open()){
        ui->statusbar->showMessage("DB connected successfuly: "+db.databaseName());
        //link model to table in form
        model = new QSqlTableModel(this,db);
        model->setTable("USERS");
        model->select();
        ui->tableView->setModel(model);
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

