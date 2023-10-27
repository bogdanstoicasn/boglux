#include "../lib/command_parsing.h"
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

uint8_t *get_line()
{
	uint64_t position = 0;
	uint64_t size = BUFFSIZE;
	uint8_t *buff = malloc(BUFFSIZE * sizeof(char));

	if (!buff) {
		fprintf(stderr, "%sdash: Allocation errors%s\n", YELLOW, RESET);
		exit(EXIT_FAILURE);
	}

	uint8_t c;
	while (1) {
		c = getchar();
		if (c == EOF || c == '\n') {
			buff[position] = '\0';
			return buff;
		} else
			buff[position] = c;
		
		++position;

		if (position >= size) {
			size += BUFFSIZE;
			buff = realloc(buff, size);
			if (!buff) {
				fprintf(stderr, "%sdash: Allocation errors%s\n", YELLOW, RESET);
				exit(EXIT_FAILURE);
			}
		}
	}
}

uint8_t **split_line(uint8_t *line)
{
	uint64_t position = 0;
	uint64_t size = BUFFSIZE;

	uint8_t **tokens = malloc(BUFFSIZE * sizeof(uint8_t *));
	uint8_t *token;
	if (!tokens) {
		fprintf(stderr, "%sdash: Allocation errors%s\n", YELLOW, RESET);
		exit(EXIT_FAILURE);
	}

	token = strtok(line, TOKEN_DELIM);
	while (token) {
		tokens[position] = token;
		++position;

		if (position >= size) {
			size += BUFFSIZE;
			tokens = realloc(tokens, size * sizeof(uint8_t *));
			if (!tokens) {
				fprintf(stderr, "%sdash: Allocation errors%s\n", YELLOW, RESET);
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOKEN_DELIM);
	}
	tokens[position] = NULL;

	return tokens;
}

uint64_t exit_shell()
{
	return 0;
}

uint64_t execute_shell(uint8_t **args)
{
	pid_t cpid;
	int status;

	if (strcmp(args[0], "exit") == 0) {
		return exit_shell();
	}

	cpid = fork();

	if (cpid == 0) {
		if (execvp(args[0], args) < 0)
			printf("dash: command not found: %s\n", args[0]);
		exit(EXIT_FAILURE);

	} else if (cpid < 0)
		printf(YELLOW "Error forking" RESET "\n");
	else {
		waitpid(cpid, &status, WUNTRACED);
	}

  return 1;
}