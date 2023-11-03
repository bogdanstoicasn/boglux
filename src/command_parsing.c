#include "../lib/command_parsing.h"

char *get_line()
{
	int position = 0;
	int size = BUFFSIZE;
	char *buff = malloc(BUFFSIZE * sizeof(char));

	if (!buff) {
		fprintf(stderr, "%sdash: Allocation errors%s\n", YELLOW, RESET);
		exit(EXIT_FAILURE);
	}

	char c;
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

char **split_line(char *line)
{
	int position = 0;
	int size = BUFFSIZE;

	char **tokens = malloc(BUFFSIZE * sizeof(char *));
	char *token;
	char **safeguard;
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
			safeguard = tokens;
			tokens = realloc(tokens, size * sizeof(char *));
			if (!tokens) {
				free(safeguard);
				fprintf(stderr, "%sdash: Allocation errors%s\n", YELLOW, RESET);
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOKEN_DELIM);
	}

	tokens[position] = NULL;

	return tokens;
}
