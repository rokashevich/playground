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

  // Соединяем сигналы смена режима от кнопок edit и select.
  connect(this, &MainWindow::modeSelect, model_1_, &SimpleModel::onModeSelect);
  connect(this, &MainWindow::modeSelect, model_2_, &SimpleModel::onModeSelect);
  connect(this, &MainWindow::modeSelect, model_3_, &SimpleModel::onModeSelect);
  connect(this, &MainWindow::modeEdit, model_1_, &SimpleModel::onModeEdit);
  connect(this, &MainWindow::modeEdit, model_2_, &SimpleModel::onModeEdit);
  connect(this, &MainWindow::modeEdit, model_3_, &SimpleModel::onModeEdit);
  connect(this, &MainWindow::modeSelect, this, &MainWindow::onModeSelect);
  connect(this, &MainWindow::modeEdit, this, &MainWindow::onModeEdit);

  // По умолчанию поля редактирования disabled, таблицы наоборот enabled.
  connect(ui->button_edit, &QPushButton::clicked, this,
          [this]() { emit modeEdit(); });
  connect(ui->button_save, &QPushButton::clicked, this,
          [this]() { emit modeSelect(); });
  emit modeSelect();
}

void MainWindow::onAnySelectionChanged(const QItemSelection &selected1,
                                       const QItemSelection &selected2) {
  Q_UNUSED(selected2)

  // Снятие выделения так же пораждает сигнал selectionChanged, с пустым
  // кол-вом индексов - эти сигнал игнорируем.
  if (selected1.indexes().count() == 0) return;

  QItemSelectionModel *m =
      dynamic_cast<QItemSelectionModel *>(QObject::sender());
  emit notifyAllSelectionChanged(m);

  // Получаем содержимое выбранной строки для отображения в форме
  // редактирования.
  QString word1 = selected1.indexes().at(0).data().toString();
  QString word2 = selected1.indexes().at(1).data().toString();
  ui->edit_1->setText(word1);
  ui->edit_2->setText(word2);
}

void MainWindow::onModeEdit() {
  ui->edit_1->setEnabled(true);
  ui->edit_2->setEnabled(true);
}

void MainWindow::onModeSelect() {
  ui->edit_1->setDisabled(true);
  ui->edit_2->setDisabled(true);
}

MainWindow::~MainWindow() { delete ui; }
