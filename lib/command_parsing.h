#ifndef H_PARSING_H
#define H_PARSING_H

#define BUFFSIZE 1024

#define YELLOW "\033[0;33m"
#define RESET "\e[0m"

#define TOKEN_DELIM " \t\r\n"

uint8_t *get_line();
uint8_t **split_line(uint8_t *line);
uint64_t exit_shell();
uint64_t execute_shell(uint8_t **args);

#endif