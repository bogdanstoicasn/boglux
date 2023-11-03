#include "../lib/command_execute.h"
#include "../lib/command_build.h"
#include "../lib/command_parsing.h"

void signal_handler_parent(int signum)
{
    (void)signum;
    printf("\n");
}

void signal_handler_child(int signum)
{
    if (signum == SIGINT)
        exit(EXIT_FAILURE);
}

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
    signal(SIGINT, signal_handler_parent);

	if (cpid == 0) {
        signal(SIGINT, signal_handler_child);
		if (execvp(args[0], args) < 0) {
            perror("ERROR execvp");
            free(*args);
            free(args);
            // if child process fails we must free the mem of command
        }
		exit(EXIT_FAILURE);

	} else if (cpid < 0)
		perror("ERROR");
	else {
        status = 1;
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
    int status, count = 0;

    system("clear");
    shell_center_text("\033[1mBOGLUX\033[0m\n\n");

    do {
        printf("> ");
        line = get_line();

        shell_history_saver(line, &count);

        args = split_line(line);
        status = execute_shell(args);

        free(line);
        free(args);
    } while (status);

    shell_history_delete();
}