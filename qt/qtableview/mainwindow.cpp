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
  ui->tableView->horizontalHeader()->setVisible(true);

  SpinBoxDelegate *delegate = new SpinBoxDelegate;
  ui->tableView->setItemDelegate(delegate);

  connect(ui->tableView, &QTableView::clicked, this,
          [](const QModelIndex &index) {
            qDebug() << "Клик в клетке" << index.row() << "," << index.column();
          });

  connect(ui->tableView->selectionModel(),
          &QItemSelectionModel::selectionChanged, this,
          [](const QItemSelection &selected1, const QItemSelection &selected2) {
            qDebug() << "selected row =" << selected1.indexes().at(0).row();
          });

  connect(ui->tableView,&QTableView::doubleClicked,this,[](const QModelIndex &index) {
    qDebug() << "Двойной клик в клетке" << index.row() << "," << index.column();
  });
}

MainWindow::~MainWindow()
{
  delete ui;
}

