# Everything you need to know to start coding your own shell

### PID & PPID

A process is an instance of an executing program, that has a unique process ID. This process ID is used by many functions and system calls to interact with and manipulate processes. In order to retrieve the current process' ID, you can use the system call getpid (man 2 getpid):

In the pid.c,  every time you run the program, a new process is created, and its ID is different.

Each process has a parent: the process that created it. It is possible to get the PID of a parent process by using the getppid system call (man 2 getppid), from within the child process.

0. ppid.c - A program that prints the PID of the parent process.
Run the program several times within the same shell. It should be the same.
echo $$ print the same value ?
echo $$ prints the PID of the current process because the parent of the process is the bash

```
$gcc -Wall -Wextra -Werror -pedantic ppid.c  -o ppid
$./ppid
2248
$echo $$
2248
$ps
  PID TTY          TIME CMD
 2248 pts/13   00:00:00 bash
 5103 pts/13   00:00:00 ps
$
```

1. max_pid.sh - A shell script that prints the maximum value a process ID can be.

/proc/sys/kernel/pid_max (since Linux 2.5.34)
This  file  specifies  the  value at which PIDs wrap around (i.e., the value in this file is one greater than the maximum PID).  The
default value for this file, 32768, results in the same range of PIDs as on earlier kernels.  On 32-bit platforms, 32768 is the max‐
imum value for pid_max.  On 64-bit systems, pid_max can be set to any value up to 2^22 (PID_MAX_LIMIT, approximately 4 million)


```
$sh ./max_pid.sh
32768
$
```

### Arguments

The command line arguments are passed through the main function: int main(int ac, char \**av);

* av is a NULL terminated array of strings
* ac is the number of items in av
* av[0] usually contains the name used to invoke the current program. av[1] is the first argument of the program, av[2] the second, and so on.

0. av.c -  A program that prints all the arguments, without using ac.
1. prompt.c - A program that prints "$ ", wait for the user to enter a command, prints it on the next line.4
2. strtok.c - A function that splits a string and returns an array of each word of the string.

### Executing a program

exec.c - using execv to execute another program which replaces previous processes memory in place.

### Creating processes

fork.c - using fork

Note: Using the return value of fork, it is possible to know if the current process is the father or the child: fork will return 0 to the child, and the PID of the child to the father.


### Wait

wait.c - using wait

The wait system call (man 2 wait) suspends execution of the calling process until one of its children terminates.

### fork + wait + execve

fork_wait_exec.c -  A program that executes the command ls -l /tmp in 5 different child. Each child is created by the same process (the father).  Waits for a child to exit before creating a new child.

### super simple shell

shell.c -  A first version of a super simple shell that can run commands with their full path, without any argument.

### File information

stat.c - using start

The stat (man 2 stat) system call gets the status of a file. On success, zero is returned. On error, -1 is returned.

### find a file in the PATH

_which.c -  A program that looks for files in the current PATH.

* Usage: _which filename ...


### Environment

Every process comes with an environment. When a new process is created, it inherits a copy of its parent's environment. To access the entire environment within a process, you have several options:

 * the main function
 * the global variable environ (man environ)

 0. printenv with environ

 environ.c - A program that prints the environment using the global variable environ.

 1. env vs environ

 env_environ.c - A program that prints the address of env (the third parameter of the main function) and environ (the global variable).

 Both are at the same address -> envp ~ environ

 2. getenv() - A function that gets an environment variable. (without using getenv)

Prototype: char *_getenv(const char *name);
man 3 getenv

getenv.c - using _getenv

3. PATH
path.c - A program that prints each directory contained in the the environment variable PATH, one directory per line.

4.PATH

path_list.c - A program that builds a linked list of the PATH directories

5. setenv

setenv.c -  A program that changes or adds an environment variable (without using setenv).

Prototype: int _setenv(const char *name, const char *value, int overwrite);
man 3 setenv

6. unsetenv

unsetenv.c - A program that deletes the variable name from the environment (without using unsetenv).

Prototype: int _unsetenv(const char *name);
man 3 unsetenv
