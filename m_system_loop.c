#include "madifort.h"

/**
 * shell_loop - Main shell loop.
 * @info: The parameter & return info struct.
 * @av: The argument vector from main().
 *
 * Return: 0 on success, 1 on error, or error code.
 */
int shell_loop(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	for (; r != -1 && builtin_ret != -2;)
	{
		clear_shell_info(info);
		if (interactive_shell(info))
			display_string("$ ");
		display_error_character(BUFFER_FLUSH);
		r = read_input(info);
		if (r != -1)
		{
			set_shell_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_command(info);
		}
		else if (interactive_shell(info))
			write_character('\n');
		free_shell_info(info, 0);
	}

	write_history_to_file(info);
	free_shell_info(info, 1);

	if (!interactive_shell(info) && info->status)
		exit(info->status);

	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}

	return (builtin_ret);
}

/**
 * find_builtin_command - Finds a builtin command.
 * @info: The parameter & return info struct.
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit().
 */
int find_builtin_command(info_t *info)
{
	int m, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", exit_shell},
		{"env", display_environment},
		{"help", display_help},
		{"history", display_history},
		{"setenv", set_environment_var},
		{"unsetenv", unset_environment_var},
		{"cd", change_directory},
		{"alias", manage_alias},
		{NULL, NULL}
	};

	for (m = 0; builtintbl[m].type; m++)
		if (compare_strings(info->argv[0], builtintbl[m].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[m].func(info);
			break;
		

	return (built_in_ret);
}

/**
 * find_command - Finds a command in PATH.
 * @info: The parameter & return info struct.
 *
 * Return: void.
 */
void find_command(info_t *)
{
int m;
int f;
char *path = NULL;

	info->path = info->argv[0];

	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	for (m = 0, f = 0; info->arg[m]; m++)
		if (!is_delimiter(info->arg[m], " \t\n"))
			f++;

	if (!f)
		return;

	path = duplicate_characters(info, get_environment_var(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_command(info);
	}
	else
	{
		if ((interactive(info) || get_environment_var(info, "PATH=")
			|| info->argv[0][0] == '/') && is_command(info, info->argv[0]))
			fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			display_custom_error(info, "not found\n");
		}
	}
}

/**
 * fork_command - Forks an exec thread to run cmd.
 * @info: The parameter & return info struct.
 *
 * Return: void.
 */
void fork_command(info_t *)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}

	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, environment_get(info)) == -1)
		{
			free_shell_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));

		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				display_custom_error(info, "Permission denied\n");
		}
	}
}

