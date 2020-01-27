#include "mainwindow.h"
#include <QDebug>
#include <QStringList>
#include <QVector>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  Type1 original_db1 = {{"a1", "A1"}, {"a2", "A2"}};
  Type1 original_db2 = {{"b1", "B1"}, {"b2", "B2"}, {"b3", "B3"}};
  Type1 original_db3 = {{"c1", "C1"}, {"c2", "C2"}, {"c3", "C3"}, {"c4", "C4"}};

  ui->setupUi(this);

  model_1_ = new SimpleModel(ui->table_1);
  model_1_->feed(original_db1);
  ui->table_1->setModel(model_1_);

  model_2_ = new SimpleModel(ui->table_2);
  model_2_->feed(original_db2);
  ui->table_2->setModel(model_2_);

  model_3_ = new SimpleModel(ui->table_3);
  model_3_->feed(original_db3);
  ui->table_3->setModel(model_3_);

  connect(ui->table_1->selectionModel(), &QItemSelectionModel::selectionChanged,
          this, &MainWindow::any_selection_changed);
  connect(ui->table_2->selectionModel(), &QItemSelectionModel::selectionChanged,
          this, &MainWindow::any_selection_changed);
  connect(ui->table_3->selectionModel(), &QItemSelectionModel::selectionChanged,
          this, &MainWindow::any_selection_changed);

  connect(this, &MainWindow::integral_selection_changed, model_1_,
          &SimpleModel::integral_selection_changed);
  connect(this, &MainWindow::integral_selection_changed, model_2_,
          &SimpleModel::integral_selection_changed);
  connect(this, &MainWindow::integral_selection_changed, model_3_,
          &SimpleModel::integral_selection_changed);

  //  ui->tableView->horizontalHeader()->setVisible(true);

  //  connect(ui->tableView, &QTableView::clicked, this,
  //          [](const QModelIndex &index) {
  //            qDebug() << "Клик в клетке" << index.row() << "," <<
  //            index.column();
  //          });

  //  connect(ui->tableView->selectionModel(),
  //          &QItemSelectionModel::selectionChanged, this,
  //          [](const QItemSelection &selected1, const QItemSelection
  //          &selected2) {
  //           qDebug() << "selected row =" << selected1.indexes().at(0).row();
  //          });

  //  connect(ui->tableView, &QTableView::doubleClicked, this,
  //          [](const QModelIndex &index) {
  //            qDebug() << "Двойной клик в клетке" << index.row() << ","
  //                     << index.column();
  //          });

  //  connect(ui->buttonSelectDown, &QPushButton::clicked, this, [this]() {
  //    QItemSelectionModel *sm = ui->tableView->selectionModel();
  //    int selected_row = -1;
  //    int selected_rows = sm->selection().indexes().count();
  //    if (selected_rows > 0) {
  //      selected_row = sm->selection().indexes().at(0).row();
  //    }
  //    int max_row = ui->tableView->model()->rowCount() - 1;
  //    int next_row = 0;
  //    if (selected_row < max_row) {
  //      next_row = selected_row + 1;
  //    }
  //    QModelIndex next_index = ui->tableView->model()->index(next_row, 0);
  //    ui->tableView->setCurrentIndex(next_index);
  //  });
}

MainWindow::~MainWindow() { delete ui; }
