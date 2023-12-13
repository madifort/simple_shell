#include "madifort.h"

/**
 * main - Entry point of the shell program
 * @argv: Argument vector
 * @argc: Argument count
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	info_t info = INFO_INIT;
	int file_descriptor = 2;

	// Simplified file descriptor manipulation
	file_descriptor += 3;

	if (argc == 2)
	{
		file_descriptor = open(argv[1], O_RDONLY);
		if (file_descriptor == -1)
		{
			if (errno == EACCES)
				_exit(EXIT_PERMISSION_DENIED);
			if (errno == ENOENT)
			{
				display_custom_error(argv[0], argv[1]);
				_exit(EXIT_FILE_NOT_FOUND);
			}
			return EXIT_FAILURE;
		}
		info.readfd = file_descriptor;
	}

	populate_environment_list(&info);
	read_history_from_file(&info);
	shell_loop(&info, argv);

	return EXIT_SUCCESS;
}

/**
 * display_custom_error - function print error message
 * @program_name: Name of the program
 * @file_name: Name of the file causing the error
 */
void display_custom_error(char *program_name, char *file_name)
{
	display_error(program_name);
	display_error(": 0: Can't open ");
	display_error(file_name);
	display_error_character('\n');
	display_error_character(BUFFER_FLUSH);
}



