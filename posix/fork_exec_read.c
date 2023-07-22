#include <stdlib.h> /* For exit */
#include <string.h> /* For strlen */

#define READ 0  /* Read end of pipe */
#define WRITE 1 /* Write end of pipe */
char *phrase = "This is a test phrase.";
main() {
  int pid, fd[2], bytes;
  char message[100];
  int fd1[2];
  char buffer[1];
  int ret;

  if (pipe(fd) == -1) { /* Create a pipe */
    perror("pipe");
    exit(1);
  }
  if (pipe(fd1) == -1) { /* Create a pipe */
    perror("pipe");
    exit(1);
  }
  if ((pid = fork()) == -1) { /* Fork a child */
    perror("fork");
    exit(1);
  }
  if (pid == 0) {      /* Child, writer */
    close(fd[READ]);   /* Close unused end */
    close(fd1[WRITE]); /*Close write  end of the 2nd pipe*/
    write(fd[WRITE], phrase, strlen(phrase) + 1);
    close(fd[WRITE]); /* Close used end */
    /*For synchronisation let the child try to
    read from the 2nd pipe.
    The function read, will return 0 only when the
    parent terminates and in this we are
    not interested if at all anything read or not.
    The read statement below, will return only if the
    parent has terminated, thus ensures that the
    child terminates only after the parent*/
    ret = read(fd1[READ], buffer, 1);
  }

  else {              /* Parent, reader */
    close(fd[WRITE]); /* Close unused end */
    close(fd1[READ]); /*Close read end of the 2nd pipe*/
    bytes = read(fd[READ], message, sizeof(message));
    printf("Read %d bytes: %s\n", bytes, message);
    close(fd[READ]); /* Close used end */
  }
}