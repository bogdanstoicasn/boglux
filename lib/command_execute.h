#ifndef H_COMM_EXE_H
#define H_COMM_EXE_H

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>

void signal_handler_parent(int signum);
void signal_handler_child(int signum);

int shell_builtins();
int launch_shell(char **args);
int execute_shell(char **args);
void loop_shell();

#endif