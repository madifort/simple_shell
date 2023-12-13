#include "madifort.h"

/**
 * exit_shell- function exits the shell.
 * @info: Structure containing potential arguments.
 *
 * Return: Exits with a given exit status (0) if info->argv[0] != "exit".
 */
int exit_shell(info_t *info)
{
	int exit_check;

	if (info->argv[1])
	{
		exit_check = convert_error_to_integer(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			display_custom_error(info, "Illegal number: ");
			display_error(info->argv[1]);
			display_error_character('\n');
			return (1);
		}
		info->err_num = convert_error_to_integer(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * change_directory - function changes the current directory of the process.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int change_directory(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		display_string("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1])
	{
		dir = get_environment_var(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = get_environment_var(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (compare_strings(info->argv[1], "-") == 0)
	{
		if (!get_environment_var(info, "OLDPWD="))
		{
			display_string(s);
			write_character('\n');
			return (1);
		}
		display_string(get_environment_var(info, "OLDPWD=")), write_character('\n');
		chdir_ret = chdir((dir = get_environment_var(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);

	if (chdir_ret == -1)
	{
		display_custom_error(info, "can't cd to ");
		display_error(info->argv[1]), display_error_character('\n');
	}
	else
	{
		set_variable_environment(info, "OLDPWD", get_environment_var(info, "PWD="));
		set_variable_environment(info, "PWD", getcwd(buffer, 1024));
	}

	return (0);
}

/**
 * display_help - Provides help information.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int display_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	display_string("Help call works. Function not yet implemented.\n");

	if (0)
		display_string(*arg_array); /* Temp unused workaround */

	return (0);
}

