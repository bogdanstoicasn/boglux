#include "../lib/command_build.h"
#include "../lib/command_execute.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <string.h>

const char *builtin_str[4] = {
  "cd",
  "help",
  "exit",
  "history"
};

int (*const builtin_func[]) (char **) = {
	&shell_cd,
	&shell_help,
	&shell_exit,
	&shell_history_saver
};

void shell_center_text(const char *text)
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	int terminal_width = w.ws_col;
	int text_length = strlen(text);
	int padding = (terminal_width + text_length) / 2;

	for (int i = 0; i < padding - text_length / 2; i++)
		putchar(' ');
	printf("%s", text);
}

int shell_exit()
{
	return 0;
}

int shell_cd(char **args)
{
	const char *dir = (char *)args[1];
	if (args[1] == NULL)
		dir = getenv("HOME");

    if (chdir(dir) != 0)
		perror("boglux: expected argument to \"cd\"\n");

    return 1;
}

int shell_help(char **args)
{
	(void)args;
    shell_center_text("\033[1mBOGLUX\n\n");
	printf("The following commands are built in:\n");
	for (int i = 0 ; i < shell_builtins(); i++) {
		printf(" %s\t", builtin_str[i]);
		if ((i & 3) == 0 && i != 0)
			printf("\n");
	}
	printf("\n\nThe commands above don't have a man page.\033[0m\n");
    return 1;
}

// TODO: implement command saving using different process
// open the file ex: fopen("/home/bogdan/cmd_hisotry.txt", "a");
int shell_history_saver(char **args)
{
	(void)args;
	return 1;
}
