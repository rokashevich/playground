#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractTableModel>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class SimpleModel: public QAbstractTableModel {
  Q_OBJECT
private:
  int rowCount(const QModelIndex &parent) const {
    return 4;
  }
  int columnCount(const QModelIndex &parent) const {
    return 4;
  }
  QVariant data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
            QString unswer = QString::number(index.row()) + "," + QString::number(index.column());
            return QVariant(unswer);
        }
        return QVariant();
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
