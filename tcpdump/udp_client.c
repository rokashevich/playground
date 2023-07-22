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
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  // 2. Настраиваем сокет - интерфейс/порт.
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr.sin_port = htons(8080);

  // 3. recvfrom()/sendto()
  char buf[] = "Hello, World!";
  socklen_t len;
  sendto(sockfd, (const char *)buf, strlen(buf), MSG_CONFIRM,
         (const struct sockaddr *)&servaddr, sizeof(servaddr));
  int n = recvfrom(sockfd, (char *)buf, 4096, MSG_WAITALL,
                   (struct sockaddr *)&servaddr, &len);
  buf[n] = '\0';
  printf("Sent and got back: %s\n", buf);

  // 5. close() - закрываем сокет.
  close(sockfd);
  return 0;
}