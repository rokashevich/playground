#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QPushButton>
#include <QThread>
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  QPushButton *b_;
};

class Worker : public QObject {
  Q_OBJECT
 public slots:
  void process() {
    qDebug() << this << "processing started";
    QThread::sleep(5);
    qDebug() << this << "processing finished";
  }
};

#endif  // MAINWINDOW_H
