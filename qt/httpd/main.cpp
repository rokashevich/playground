// код отсюда: https://stackoverflow.com/a/32931195
// плагин для отображения в браузерах: https://add0n.com/json-beautifier.html
#include <QCoreApplication>

#include "httpd.h"

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  Httpd server;
  return a.exec();
}
