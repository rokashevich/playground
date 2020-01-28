#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QAbstractTableModel>
#include <QDebug>
#include <QItemSelection>
#include <QMainWindow>
#include <QSpinBox>
#include <QStringList>
#include <QStyledItemDelegate>
#include <QTableView>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

typedef QVector<QStringList> Type1;
typedef QVector<QStringList> Type2;
typedef QVector<QStringList> Type3;

class SimpleModel : public QAbstractTableModel {
  Q_OBJECT
 public:
  SimpleModel(QTableView *table) : table_(table) { table->setModel(this); }
  template <typename T>
  void feed(T db) {
    db_ = db;
    emit layoutChanged();
  }

 private:
  QVector<QStringList> db_;
  QTableView *table_;
  Qt::ItemFlags flags(const QModelIndex &index) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    return flags;
  }
  int rowCount(const QModelIndex &parent) const { return db_.count(); }
  int columnCount(const QModelIndex &parent) const { return 2; }
  QVariant data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
      QStringList row = db_.at(index.row());
      QString column_value = row.at(index.column());
      return QVariant(column_value);
    }
    return QVariant();
  }

 public slots:
  void onNotifyAllSelectionChanged(QItemSelectionModel *m) {
    // Очищаем выделение в таблице только если пришедший сигнал не от тебя
    // самого.
    if (this != dynamic_cast<SimpleModel *>(m->model())) {
      table_->clearSelection();
    }
  }
  void onModeEdit() { table_->setDisabled(true); }
  void onModeSelect() { table_->setEnabled(true); }
};

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
 signals:
  void notifyAllSelectionChanged(QItemSelectionModel *m);
  void modeEdit();
  void modeSelect();
 public slots:
  void onAnySelectionChanged(const QItemSelection &, const QItemSelection &);
  void onModeEdit();
  void onModeSelect();

 private:
  Ui::MainWindow *ui;
  SimpleModel *model_1_;
  SimpleModel *model_2_;
  SimpleModel *model_3_;
};
#endif  // MAINWINDOW_H
