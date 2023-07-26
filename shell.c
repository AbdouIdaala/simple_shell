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

	while (1)
	{
		/*prompt();*/
		line = _getline();
		if (*line != '\0')
		{
			args = parseline(line);
			execute(args);
		}
		free(line);
		line = NULL;
	}
	exit(EXIT_SUCCESS);
}
