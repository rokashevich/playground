#include "mainwindow.h"

#include <QDebug>
#include <QObject>
#include <QThread>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  QWidget *wdg = new QWidget(this);
  QVBoxLayout *vbl = new QVBoxLayout(wdg);
  this->setCentralWidget(wdg);
  b_ = new QPushButton("X");
  vbl->addWidget(b_);

  Worker *w = new Worker;

  QThread *t = new QThread();
  w->moveToThread(t);
  t->start();

  connect(b_, &QPushButton::clicked, w, &Worker::process);
}

MainWindow::~MainWindow() {}
