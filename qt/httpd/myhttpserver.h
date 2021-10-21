#ifndef MYHTTPSERVER
#define MYHTTPSERVER
#include <QCoreApplication>
#include <QDebug>
#include <QNetworkInterface>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <iostream>

class myHTTPserver : public QObject {
  Q_OBJECT
 public:
  explicit myHTTPserver(QObject *parent = 0);
  ~myHTTPserver();
  QTcpSocket *socket;
 public slots:
  void myConnection();

 private:
  qint64 bytesAvailable() const;
  QTcpServer *server;
 signals:
};
#endif
