#ifndef H_COMM_BUILD_H
#define H_COMM_BUILD_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <string.h>

extern const char *builtin_str[4];
extern int (*const builtin_func[]) (char **);

void shell_center_text(const char *text);

int shell_cd(char **args);
int shell_help(char **args);

int shell_history_saver(char *line, int *count);
void shell_history_delete();
int shell_history(char **args);

int shell_exit();

#endif