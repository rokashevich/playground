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
  SimpleModel(QTableView *tv) : tv_(tv) {}
  template <typename T>
  void feed(T db) {
    db_ = db;
  }
  QVector<QStringList> db_;

 private:
  QTableView *tv_;

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
  void integral_selection_changed(SimpleModel *m) {
    if (this != m) {
      tv_->selectionModel()->clearSelection();
    } else {
      // qDebug() << m->db_;
    }
  }
 signals:
  void clearSelection();
};

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
 signals:
  void integral_selection_changed(SimpleModel *m);
 public slots:
  void any_selection_changed(const QItemSelection &selected1,
                             const QItemSelection &selected2) {
    QObject *obj = sender();
    QItemSelectionModel *m = static_cast<QItemSelectionModel *>(obj);
    SimpleModel *s = static_cast<SimpleModel *>(m->model());
    emit integral_selection_changed(s);
    // qDebug() << "selected row =" << selected1.indexes().at(0).row();
  }

 private:
  Ui::MainWindow *ui;
  SimpleModel *model_1_;
  SimpleModel *model_2_;
  SimpleModel *model_3_;
};
#endif  // MAINWINDOW_H
