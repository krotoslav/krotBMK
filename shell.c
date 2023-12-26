#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SEP " \t\r\n\a"

int cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "ожидается аргумент для \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("sh");
    }
  }
  return 1;
}

int exit_(char **args)
{
  return 0;
}

int launch(char **arguments)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    if (execvp(arguments[0], arguments) == -1) {
      perror("sh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    perror("sh");
  } else {
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    return 1;
  }

  if (strcmp(args[0], "cd") == 0) {
    return cd(args);
  } else if (strcmp(args[0], "exit") == 0) {
    return exit_(args);
  }

  return launch(args);
}

char **split_line(char *line)
{
  int bufsize = 64, position = 0;
  // массив строк
  char **commands = malloc(bufsize * sizeof(char*));
  // строка
  char *command;
  // если маллок не сработал, экзит
  if (!commands) {
    exit(EXIT_FAILURE);
  }
  // получаем указатель на первое выделенное слово
  command = strtok(line, SEP);
  while (command != NULL) {
    // записываем строку в массив
    commands[position] = command;
    position++;
    // если наш массив меньше чем у нас слов, то расширяем массив
    if (position >= bufsize) {
      bufsize += 64;
      commands = realloc(commands, bufsize * sizeof(char*));
      // если не смогли расширить, экзит
      if (!commands) {
        exit(EXIT_FAILURE);
      }
    }
    // продолжаем считывать слова из строки
    command = strtok(NULL, SEP);
  }
  commands[position] = NULL;
  return commands;
}

char *read_line(void)
{
  char *line = NULL;
  ssize_t bufsize = 0; 
  getline(&line, &bufsize, stdin); 
  return line;
}

void shell(void) // функция шел
{
  char *line;
  char **args;
  int status;

  do {
    printf("$ ");
    line = read_line(); 
    args = split_line(line);// разделили строку на массив строк 
    status = execute(args);// слова из сплитлайна передаются в аргс

    free(line);
    free(args);
  } while (status);
}

int main()
{
  shell(); //запускается шел
  return 0;
}
