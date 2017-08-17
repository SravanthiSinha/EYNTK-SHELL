#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1

int main(int argc, char **argv) {
  int pipefd[2];
  pid_t cpid;
  int status;
  char *args[2] = {"/usr/bin/rev", NULL};
  char buf;

  if (argc != 2) {
    printf("Usage: %s <input>", argv[0]);
    exit(1);
  }

  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(1);
  }

  cpid = fork();
  if (cpid == -1) {
    perror("fork");
    exit(1);
  }

  if (cpid == 0) {
    close(pipefd[WRITE_END]);
    dup2(pipefd[WRITE_END], STDOUT_FILENO);
    if (dup2(pipefd[READ_END], STDIN_FILENO) == -1) {
      perror("dup2");
      return (EXIT_FAILURE);
    }
    close(pipefd[READ_END]);
    execve(args[0], args, NULL);
    exit(EXIT_SUCCESS);
  } else {
    close(pipefd[READ_END]);
    write(pipefd[WRITE_END], argv[1], strlen(argv[1]));
    close(pipefd[WRITE_END]);
    wait(&status);
    // Read from child’s stdout
    while (read(pipefd[READ_END], &buf, 1) > 0)
      write(STDOUT_FILENO, &buf, 1);

    exit(EXIT_SUCCESS);
  }
  return (0);
}
