// https://stackoverflow.com/a/32931195
#include "myhttpserver.h"

using namespace std;
void delayms(int millisecondsToWait);

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  myHTTPserver server;
  return a.exec();
}

myHTTPserver::myHTTPserver(QObject *parent) : QObject(parent) {
  server = new QTcpServer(this);
  // waiting for the web brower to make contact,this will emit signal
  connect(server, SIGNAL(newConnection()), this, SLOT(myConnection()));
  if (!server->listen(QHostAddress::Any, 8080))
    cout << "\nWeb server      could not start";
  else
    cout << "\nWeb server is waiting for a connection on port 8080";
}

void myHTTPserver::myConnection() {
  static qint16 count;  // count number to be displayed on web browser
  socket = server->nextPendingConnection();
  while (!(socket->waitForReadyRead(100)))
    ;  // waiting for data to be read from web browser

  char webBrowerRXData[1000];
  int sv = socket->read(webBrowerRXData, 1000);
  cout << "\nreading web browser data=\n";
  for (int i = 0; i < sv; i++) cout << webBrowerRXData[i];
  cout << "\n";

  socket->write("HTTP/1.1 200 OK\r\n");  // \r needs to be before \n
  socket->write("Content-Type: text/html\r\n");
  socket->write("Connection: close\r\n");
  socket->write("Refresh: 1\r\n\r\n");  // refreshes web browser     every
                                        // second. Require two \r\n.

  socket->write("<!DOCTYPE html>\r\n");
  socket->write("<html><body>Number of seconds since connected.. ");
  QByteArray str;
  str.setNum(count++);  // convert int to string
  socket->write(str);
  socket->write(" </body>\n</html>\n");

  socket->flush();
  connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
  socket->disconnectFromHost();
}

myHTTPserver::~myHTTPserver() { socket->close(); }
