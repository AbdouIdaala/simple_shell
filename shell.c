#include "shell.h"

/**
 * main - simple shell
 *
 * Return: exit with 0
 */
int main(void)
{
	char *line = NULL;
	char **args = NULL;
	int status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			prompt();
		line = _getline(status);
		if (line && *line != '\0')
		{
			args = parseline(line);
			if (args)
				status = execute(args);
		}
		free(line);
		line = NULL;
	}
	exit(EXIT_SUCCESS);
}
