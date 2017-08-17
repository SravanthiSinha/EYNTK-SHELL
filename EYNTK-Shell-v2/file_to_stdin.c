#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int fd, status;
  pid_t child_pid;
  char c;
  char *args[2] = {"/usr/bin/rev", NULL};

  if (argc != 2)
    exit(1);
  fd = open(argv[1], O_RDONLY);
  child_pid = fork();
  if (child_pid == 0) {
    if (dup2(fd, STDIN_FILENO) == -1) {
      perror("dup2");
      return (EXIT_FAILURE);
    }
    close(fd);
    execve(args[0], args, NULL);
  }
  if (child_pid != 0) {
    close(fd);
    wait(&status);
  }
  return (EXIT_SUCCESS);
}
