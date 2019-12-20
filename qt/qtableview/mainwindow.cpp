#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  model_ = new SimpleModel;
  ui->tableView->setModel(model_);

  connect(ui->tableView,&QTableView::clicked,this,[](const QModelIndex &index) {
    qDebug() << "Клик в клетке" << index.row() << "," << index.column();
  });

  connect(ui->tableView,&QTableView::doubleClicked,this,[](const QModelIndex &index) {
    qDebug() << "Двойной клик в клетке" << index.row() << "," << index.column();
  });
}

MainWindow::~MainWindow()
{
  delete ui;
}

