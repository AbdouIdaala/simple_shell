#include "shell.h"

/**
 * prompt - display a prompt
 *
 * Return: void
 */
void prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}

/**
 * free_arr - free memory allocated for args
 * @args: double pointer to an array of strings
 *
 * Return: void
 */
void free_arr(char **args)
{
	int i = 0;

	if (args)
	{
		while (args[i])
			free(args[i++]);
		free(args[i]);
		free(args);
	}
}

/**
 * _getline - get the line entered by the user
 * @status: the exit status
 *
 * Return: the line on success
 */
char *_getline(int status)
{
	ssize_t nread = 0;
	size_t len = 0, i = 0;
	char *line = NULL, *end = NULL;
	char *linecopy = NULL;

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		exit(EXIT_SUCCESS);
	}
	line[nread - 1] = '\0';
	if (strcmp(line, "exit") == 0)
	{
		free(line);
		exit(WEXITSTATUS(status));
	}
	if (strcmp(line, "env") == 0)
	{
		while (environ[i])
		{
			write(STDOUT_FILENO, environ[i], strlen(environ[i]));
			write(STDOUT_FILENO, "\n", 1);
			i++;
		}
		free(line);
		return (NULL);
	}
	for (end = line; (*end == ' ' || *end == '\t'); end++)
	;
	linecopy = strdup(end);
	free(line);
	return (linecopy);
}

/**
 * parseline - parse a line into valid arguments
 * @line: pointer to a string
 *
 * Return: double pointer to an array of strings on success
 */
char **parseline(char *line)
{
	const char *delim = " \t\n";
	char *token;
	char **args = malloc(sizeof(char *) * (MAX_ARGS + 1));
	int i = 0;

	if (!args)
		return (NULL);

	token = strtok(line, delim);
	while (token)
	{
		args[i++] = strdup(token);
		token = strtok(NULL, delim);
	}
	args[i] = NULL;
	return (args);
}
