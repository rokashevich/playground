#include <arpa/inet.h>  // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>  // bzero()
#include <sys/socket.h>
#include <unistd.h>  // read(), write(), close()

int main() {
  int sockfd, connfd;
  struct sockaddr_in servaddr, cli;

  // 1. socket() - cоздаём сокет.
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("socket creation failed...\n");
    exit(1);
  }

  // 2. Настраиваем сокет - интерфейс/порт.
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr.sin_port = htons(8080);

  // 3. connect() - соединяемся с адресом:портом сделавшим listen().
  if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
    printf("connection with the server failed...\n");
    exit(1);
  }

  // 4. write() - записываем в сокет.
  char buf[] = "Hello, World!";
  write(sockfd, buf, sizeof(buf));
  read(sockfd, buf, sizeof(buf));
  printf("Sent and got back: %s\n", buf);

  // 5. close() - закрываем сокет.
  close(sockfd);
}