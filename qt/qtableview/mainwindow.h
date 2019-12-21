#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractTableModel>
#include <QMainWindow>
#include <QSpinBox>
#include <QStyledItemDelegate>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class SpinBoxDelegate : public QStyledItemDelegate
{
  Q_OBJECT

public:
  SpinBoxDelegate(QObject *parent = nullptr){};

  QWidget *createEditor(QWidget *parent,
                        const QStyleOptionViewItem &/* option */,
                        const QModelIndex &/* index */) const {
    QSpinBox *editor = new QSpinBox(parent);
    editor->setFrame(false);
    editor->setMinimum(0);
    editor->setMaximum(100);

    return editor;
  }

  void setEditorData(QWidget *editor,
                                  const QModelIndex &index) const {
    int value = index.model()->data(index, Qt::EditRole).toInt();
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->setValue(value);
  }
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const {
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->interpretText();
    int value = spinBox->value();

    model->setData(index, value, Qt::EditRole);
  }

  void updateEditorGeometry(QWidget *editor,
                            const QStyleOptionViewItem &option,
                            const QModelIndex &/* index */) const {
    editor->setGeometry(option.rect);
  }
};

class SimpleModel: public QAbstractTableModel {
  Q_OBJECT
private:
  Qt::ItemFlags flags(const QModelIndex &index) const {
      Qt::ItemFlags flags = QAbstractTableModel::flags(index);
      flags |= Qt::ItemIsEditable;
      return flags;
  }
  int rowCount(const QModelIndex &parent) const {
    return 4;
  }
  int columnCount(const QModelIndex &parent) const {
    return 4;
  }
  QVariant data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
      QString unswer = QString::number(index.row()) + "," + QString::number(index.column());
      return QVariant(1);
    }
    return QVariant();
  }
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override {

  }
};

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  SimpleModel* model_;
};
#endif // MAINWINDOW_H
