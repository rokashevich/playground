#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  model_ = new SimpleModel;
  ui->tableView->setModel(model_);
}

MainWindow::~MainWindow()
{
  delete ui;
}

