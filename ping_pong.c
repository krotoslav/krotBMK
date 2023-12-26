#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int fd[2]; // массив
int count;
int pid; // идентификатор процесса 
int status; //для системного вызова wait()

void sig_handler(int sig) {// функция обработки сигнала
  if (count < 100) {
    // still ping-pong
    read(fd[0], &count, sizeof(count));
    // pid: ___ count: ___
    printf("pid: %d count: %d\n", pid, count);
    ++count;// увеличивает на 1
    write(fd[1], &count, sizeof(count));
    kill(pid, SIGUSR1);
  } else {
    // terminate all processes
      if (pid == getppid()) {
        // terminate child
        close(fd[0]);
        close(fd[1]);
        exit(0);
      } else {
        // send signal to child
        kill(pid, SIGUSR1);
      }
  }
}

int main() {
  signal(SIGUSR1, sig_handler); //установили сигнал
  pipe(fd);  // открыыли канал
  count = 0;
  pid = fork();
  if (pid != 0){
    // parent
    while (wait(&status) == -1){}
    close(fd[0]);
    close(fd[1]);
  } else {
    // child
    pid = getppid();
    write(fd[1], &count, sizeof(count));
    kill(pid, SIGUSR1);
    while (1) {}
  }
  return 0;
}
