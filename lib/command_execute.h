#ifndef H_COMM_EXE_H
#define H_COMM_EXE_H

int shell_builtins();
int launch_shell(char **args);
int execute_shell(char **args);
void loop_shell();

#endif