## Everything You Need To Know - Shell v2

DUP2

```
ls > ls_result
```

The previous command will execute ls and redirect stdout to the file named ls_result. If a file named ls_result already exists, it will be overwritten. If it does not exist, it will be created.

In this case, we need to tell ls not to print on stdout but instead in the file ls_result. If you remember your first version of the shell, we use execve to copy the ls executable into the current process. Once execve is called, we lose control on the process, and we just wait for it to exit using wait in the parent process.

So we need to manage the output redirection before executing any command with execve. Our solution is a system call (man 2) named dup2.

0. stdout to a file

stdout_to_file.c -  A program that opens a file (in write mode) and redirects stdout to this file.

1. stdout to end of a file

stdout_to_end_file.c - A program that opens a file (in read+ mode) and redirects stdout at the end of this file.

2. file to command stdin

file_to_stdin.c - A program that opens a file, and executes the command /usr/bin/rev with the file's content as input

### PIPE

```
ls | cat -e
```

We probably used it a lot without even knowing how it works: the pipe. The pipe is used to make the output of a process the input of another process. In the above command, the output of the ls command will be piped to be the input of the cat -e command.

#### Do not confuse input and arguments:

```
cat -e
```
Here, -e is an argument, but the command cat will read its input from the standard input (a.k.a stdin)

To reproduce this behaviour we will need another fantastic system call (man 2) ------> pipe !

 pipe_example.c - program creates a pipe, and then fork(2)s to create a child process; the child inherits a duplicate set of file descriptors that refer to the same pipe. After the fork(2), each process closes the descriptors that it doesn't need for the pipe (see pipe(7)). The parent then writes the string contained in the program's command-line argument to the pipe, and the child reads this string a byte at a time from the pipe and echoes it on standard output.

 ```
$ gcc -Wall -Wextra -Werror -pedantic pipe_example.c
$ ./a.out "C is fun"
C is fun
$
 ```

### DUP2 + PIPE

To create a pipe between two processes, we need to combine the functions dup2 and pipe. Here's the process: We first need to create a pipe using pipe (2), and then use dup2 (2) to redirect the output of the first command into the write end of our pipe. Finally, we need to redirect the read end of our pipe into the input of our second command.

3. stdout to command input

stdout_command_input.c - A program that pipes stdout to the command /usr/bin/rev. For this exercise, you'll need to use dup2, pipe and execve. You have to create a pipe, redirect stdout to the write end of the pipe, and redirect the read end of the pipe to be the input of rev, so everything printed on stdout using printf, write, ... should be printed reversed.

4. pipe between two processes

```
ls | rev
```

 pipe_processes.c - A program that executes the command /bin/ls in a forked process. Then, execute the command /usr/bin/rev in another forked process, but the output from ls must be piped to rev.
