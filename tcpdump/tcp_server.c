#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>  // read(), write(), close()

int main() {
  int sockfd, connfd, len;
  struct sockaddr_in servaddr, cli;

  // 1. socket() - cоздаём сокет.
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("socket creation failed...\n");
    exit(1);
  }

  // 2. Настраиваем сокет - интерфейс/порт.
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr.sin_port = htons(8080);
  // Чтобы система не держала сокет после закрытия пару минут.
  int optval = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

  // 3. bind() - связываем дескриптор сокета с адресом и портом.
  if ((bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) {
    printf("socket bind failed...\n");
    exit(1);
  }

  // 4. listen() - слушаем дескриптор (блокирующее ожидание).
  if ((listen(sockfd, 5)) != 0) {
    printf("Listen failed...\n");
    exit(1);
  }

  // 5. accept() - принимаем входящее соединение.
  // Причём для принятого соединения ОС создаёт отдельный дескриптор connfd,
  // socketfd же используется для продолжения прослушивания на входящие
  // соединения.
  len = sizeof(cli);
  connfd = accept(sockfd, (struct sockaddr*)&cli, &len);
  if (connfd < 0) {
    printf("server accept failed...\n");
    exit(1);
  }

  // 6. read()/write() - читаем из принятого соединения.
  char buf[4096];
  read(connfd, buf, sizeof(buf));
  write(connfd, buf, sizeof(buf));
  printf("Got and sent back: %s\n", buf);

  // 7. close() - закрываем сокет.
  close(sockfd);
}