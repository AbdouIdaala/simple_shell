#include "shell.h"

/**
 * check_access - check if a file has access
 * @command: the command to check
 *
 * Return: full path of the command on success
 */
char *check_access(char *command)
{
	const char *delim = ":";
	char buffer[1024];
	char *fullpath, *result, *token;

	if (access(command, F_OK) == 0)
		return (command);
	fullpath = strdup(getenv("PATH"));
	token = strtok(fullpath, delim);
	while (token)
	{
		strcpy(buffer, token);
		strcat(buffer, "/");
		strcat(buffer, command);
		result = strdup(buffer);
		if (access(result, F_OK) == 0)
		{
			free(fullpath);
			return (result);
		}
		token = strtok(NULL, delim);
		free(result);
	}
	free(fullpath);
	return (NULL);
}

/**
 * execute - execute the file
 * @args: array of strings contains the file to execute
 *
 * Return: void
 */
int execute(char **args)
{
	pid_t pid;
	int status = 0;
	char *full_path = check_access(args[0]);

	if (full_path)
	{
		pid = fork();
		if (pid == -1)
			perror("Fork");
		if (pid == 0)
		{
			execve(full_path, args, environ);
			perror(full_path);
		}
		else
			wait(&status);
		if (full_path != args[0])
			free(full_path);
		free_arr(args);
	}
	else
	{
		perror(args[0]);
		free_arr(args);
	}
	return (status);
}
