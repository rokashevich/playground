#pragma once
#include <QCoreApplication>
#include <QDebug>
#include <QNetworkInterface>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <iostream>
class Httpd : public QObject {
  Q_OBJECT
  qint64 bytesAvailable() const;
  QTcpServer *server;

 public:
  Httpd() {
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(myConnection()));
    if (!server->listen(QHostAddress::Any, 8080))
      std::cout << "Web server      could not start" << std::endl;
    else
      std::cout << "Web server is waiting for a connection on port 8080"
                << std::endl;
  }
  ~Httpd() { socket->close(); }
  QTcpSocket *socket;
 public slots:
  void myConnection() {
    socket = server->nextPendingConnection();
    while (!(socket->waitForReadyRead(100)))
      ;  // waiting for data to be read from web browser

    char webBrowerRXData[1000];
    int sv = socket->read(webBrowerRXData, 1000);
    for (int i = 0; i < sv; i++) std::cout << webBrowerRXData[i];
    std::cout << std::endl;

    QString content = "{\"seconds\":111,\"branch\":{\"a\":1,\"b\":2}}";

    socket->write("HTTP/1.1 200 OK\r\n");
    socket->write("Content-Type: application/json\r\n");
    socket->write("Content-Length:" + QByteArray::number(content.length()) +
                  "\r\n");
    socket->write("Connection: close\r\n\r\n");

    socket->write(content.toLocal8Bit());

    socket->flush();
    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
    socket->disconnectFromHost();
  }
};
