#ifndef H_COMM_BUILD_H
#define H_COMM_BUILD_H


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