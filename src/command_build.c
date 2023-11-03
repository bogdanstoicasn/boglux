#include "../lib/command_build.h"
#include "../lib/command_execute.h"

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
	&shell_history
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
int shell_history_saver(char *line, int *count)
{
	*count = *count +1;
	char *dir = getenv("HOME");
	char cpdir[128];
	strcpy(cpdir, dir);
	strcat(cpdir, "/cmd_history.txt");
	
	if (*count == 100) {
		*count = 1;
		if (remove(cpdir) != 0 ) {
			fprintf(stderr, "Error removing history file\n");
        	exit(EXIT_FAILURE);
		}
	}

	FILE *fptr = fopen(cpdir, "a");
	if (!fptr) {
		fprintf(stderr, "ERROR: shell history unsaved");
		exit(EXIT_FAILURE);
	}

	fprintf(fptr,"%s\n", line);
	fflush(fptr);
	fclose(fptr);
	return 1;
}

void shell_history_delete()
{
	char *dir = getenv("HOME");
	char cpdir[128];
	strcpy(cpdir, dir);
	strcat(cpdir, "/cmd_history.txt");
	if (remove(cpdir) != 0 ) {
		fprintf(stderr, "Error removing history file\n");
        exit(EXIT_FAILURE);
	}
}
int shell_history(char **args)
{
	(void)args;
	char *dir = getenv("HOME");
	char cpdir[128];
	strcpy(cpdir, dir);
	strcat(cpdir, "/cmd_history.txt");

	FILE *fptr = fopen(cpdir, "r");
	char c;
	while ((c = fgetc(fptr)) != EOF)
		printf("%c", c);
	
	fclose(fptr);
	return 1;
}
