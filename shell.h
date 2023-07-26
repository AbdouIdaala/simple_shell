#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 64

extern char **environ;

void prompt(void);
char *_getline(int status);
char **parseline(char *line);
char *check_access(char *command);
int execute(char **args);
void free_arr(char **args);

#endif /* _SHELL_H */
