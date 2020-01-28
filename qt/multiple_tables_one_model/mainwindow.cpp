#include "mainwindow.h"
#include <QDebug>
#include <QStringList>
#include <QVector>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  // Оригинальные данные "из вне".
  Type1 original_db1 = {{"a1", "A1"}, {"a2", "A2"}};
  Type2 original_db2 = {{"b1", "B1"}, {"b2", "B2"}, {"b3", "B3"}};
  Type3 original_db3 = {{"c1", "C1"}, {"c2", "C2"}, {"c3", "C3"}, {"c4", "C4"}};

  ui->setupUi(this);

  // Подключаем модели к таблицам.
  model_1_ = new SimpleModel(ui->table_1);
  model_1_->feed(original_db1);

  model_2_ = new SimpleModel(ui->table_2);
  model_2_->feed(original_db2);

  model_3_ = new SimpleModel(ui->table_3);
  model_3_->feed(original_db3);

  // Соединяем selectionChanged таблиц с единым приёмником anySelectionChanged.
  connect(ui->table_1->selectionModel(), &QItemSelectionModel::selectionChanged,
          this, &MainWindow::onAnySelectionChanged);
  connect(ui->table_2->selectionModel(), &QItemSelectionModel::selectionChanged,
          this, &MainWindow::onAnySelectionChanged);
  connect(ui->table_3->selectionModel(), &QItemSelectionModel::selectionChanged,
          this, &MainWindow::onAnySelectionChanged);

  // Соединяем сигнал из anySelectionChanged обратно во все модели, т.о.
  // о клике в любой таблице становится известно всем таблицам.
  connect(this, &MainWindow::notifyAllSelectionChanged, model_1_,
          &SimpleModel::onNotifyAllSelectionChanged);
  connect(this, &MainWindow::notifyAllSelectionChanged, model_2_,
          &SimpleModel::onNotifyAllSelectionChanged);
  connect(this, &MainWindow::notifyAllSelectionChanged, model_3_,
          &SimpleModel::onNotifyAllSelectionChanged);
}

MainWindow::~MainWindow() { delete ui; }
