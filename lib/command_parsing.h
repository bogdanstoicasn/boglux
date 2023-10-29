#ifndef H_PARSING_H
#define H_PARSING_H

#include <stdint.h>
#define BUFFSIZE 1024

#define YELLOW "\033[0;33m"
#define RESET "\e[0m"

#define TOKEN_DELIM " \t\r\n\a"

char *get_line();
char **split_line(char *line);

#endif
