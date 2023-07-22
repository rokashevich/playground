#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int sockfd;
  struct sockaddr_in servaddr;

  // 1. socket() - cоздаём сокет.
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    perror("socket creation failed");
    exit(1);
  }

  // 2. Настраиваем сокет - интерфейс/порт.
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;  // IPv4
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr.sin_port = htons(8080);
  // Чтобы система не держала сокет после закрытия пару минут.
  int optval = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

  // 3. bind() - связываем дескриптор сокета с адресом и портом.
  if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
    printf("socket bind failed...\n");
    exit(1);
  }

  // 4. recvfrom()/sendto()
  struct sockaddr_in cliaddr;
  memset(&cliaddr, 0, sizeof(cliaddr));
  socklen_t len = sizeof(cliaddr);

  char buf[4096];
  int n = recvfrom(sockfd, (char *)buf, 4096, MSG_WAITALL,
                   (struct sockaddr *)&cliaddr, &len);
  buf[n] = '\0';
  int a = sendto(sockfd, (const char *)buf, strlen(buf), MSG_CONFIRM,
                 (const struct sockaddr *)&cliaddr, len);
  perror("sendto");
  printf("Got and sent back: %s, %d\n", buf, a);
  // 5. close()
  // close(sockfd);
}