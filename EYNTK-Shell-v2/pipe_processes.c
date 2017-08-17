#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LS_READ 0
#define LS_WRITE 1
#define REV_READ 0
#define REV_WRITE 1

int main(int argc, char **argv) {
  pid_t cpid, cpid2;
  int status;
  int pipe_fd;
  char *args[] = {"/bin/ls", NULL};
  int pipefd[2];
  char buf;

  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(1);
  }
  cpid = fork();
  if (cpid == -1 || cpid2 == -1) {
    perror("fork");
    exit(1);
  }

  if (cpid == 0) {
    close(pipefd[LS_READ]);
    dup2(pipefd[LS_WRITE], STDOUT_FILENO);
    close(pipefd[LS_WRITE]);
    execve(args[0], args, NULL);
    perror("execve");
    exit(1);
  } else {
    wait(&status);
    cpid2 = fork();
    if (cpid2 == 0) {
      close(pipefd[REV_WRITE]);
      dup2(pipefd[REV_WRITE], STDOUT_FILENO);
      dup2(pipefd[LS_READ], STDIN_FILENO);
      close(pipefd[REV_READ]);
      args[0] = "/usr/bin/rev";
      execve(args[0], args, NULL);
      perror("execve");
      exit(1);
    } else {
      close(pipefd[LS_WRITE]);
      wait(&status);
      // Read from rev’s stdout
      while (read(pipefd[REV_READ], &buf, 1) > 0)
        write(STDOUT_FILENO, &buf, 1);
      exit(EXIT_SUCCESS);
    }
    exit(0);
  }

  retrun(0);
}
