#include "../lib/command_execute.h"
#include "../lib/command_build.h"
#include "../lib/command_parsing.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int shell_builtins()
{
    return sizeof(builtin_str) / sizeof(char *);
}

int execute_shell(char **args)
{
    if (args[0] == NULL)
        return 1;
    
    for (int i = 0 ; i < shell_builtins(); i++)
        if (strcmp(args[0], builtin_str[i]) == 0)
            return (*builtin_func[i])(args);
    
    return launch_shell(args);
}

int launch_shell(char **args)
{
	pid_t cpid;
	int status;

	cpid = fork();

	if (cpid == 0) {
		if (execvp(args[0], args) < 0) {
            perror("ERROR");
            free(*args);
            free(args);
            // if child process fails we must free the mem of command
        }
		exit(EXIT_FAILURE);

	} else if (cpid < 0)
		perror("ERROR");
	else {
		do {
			waitpid(cpid, &status, WUNTRACED);
		} while(!WIFEXITED(status) && !WIFSIGNALED(status));
        // we wait until the command is exited/killed
	}

	return 1;
}

void loop_shell()
{
    char *line;
    char **args;
    int status;

    system("clear");
    shell_center_text("\033[1mBOGLUX\033[0m\n\n");

    do {
        printf("> ");
        line = get_line();
        args = split_line(line);
        status = execute_shell(args);
        shell_history_saver(args);

        free(line);
        free(args);
    } while (status);
}