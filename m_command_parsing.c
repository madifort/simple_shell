#include "madifort.h"

/**
 * is_command - Checks if a file is an executable command.
 * @info: The info struct.
 * @path: Path to the file.
 *
 * Return: (1) if true, (0) otherwise.
 */
int is_command(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_characters - Duplicates characters from a string.
 * @pathstr: The PATH string.
 * @start: Starting index.
 * @stop: Stopping index.
 *
 * Return: Pointer becomes the new buffer.
 */
char *duplicate_characters(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int m = 0, f = 0;

	for (f = 0, m = start; m < stop; m++)
		if (pathstr[m] != ':')
			buf[f++] = pathstr[m];
	buf[f] = 0;
	return (buf);
}

/**
 * find_command_path - Finds the command in the PATH string.
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @command: The command to find.
 *
 * Return: Full path of the command if found, or NULL.
 */
char *find_command_path(info_t *info, char *pathstr, char *command)
{
	int curr_pos = 0;
	int m = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if (starts_with_substring(command, "./") && (string_length(command) > 2))
	{
		if (is_command(info, command))
			return (command);
	}
	for (; 1; m++)
	{
		if (!pathstr[m] || pathstr[m] == ':')
		{
			path = duplicate_characters(pathstr, curr_pos, m);
			if (!*path)
				concatenate_strings(path, command);
			else
			{
				concatenate_strings(path, "/");
				concatenate_strings(path, command);
			}
			if (is_command(info, path))
				return (path);
			if (!pathstr[m])
				break;
			curr_pos = m;
		}
	}
	return (NULL);
}



