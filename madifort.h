#ifndef _MADIFORT_H
#define _MADIFORT_H

#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <fcntl.h>

/* Buffer Sizes for Reading and Writing */
#define WRITE_BUFFER_SIZE 1024
#define READ_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* System getline() Options */
#define USE_STRTOK 0
#define USE_GETLINE 0
#define MAX_HISTORY 4096
#define HISTORY_FILE ".shell_history"

extern char **environ;

/* Command Chaining Flags */
#define CMD_AND 2
#define CMD_NORMAL 0
#define CMD_CHAIN 3
#define CMD_OR 1

/* Number Conversion Options */
#define CONVERT_UNSIGNED 2
#define CONVERT_LOWERCASE 1

/**
 * struct liststr - A structure for a singly linked list
 * @num: An integer value
 * @str: A pointer to a string
 * @next: A pointer to the next node in the list
 */
typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;

/**
 * struct passinfo - A structure containing pseudo-argument pass into a func.
 * @arg: A pointer to a string argument
 * @argv: A pointer to an array of strings
 * @path: A pointer to a string representing the path
 * @argc: An integer representing the argument count
 * @line_count: An unsigned integer representing the line count
 * @err_num: An integer representing the error number
 * @linecount_flag: An integer flag for line count
 * @fname: A pointer to a string representing the file name
 * @env: A pointer to the environment list
 * @history: A pointer to the history list
 * @alias: A pointer to the alias list
 * @environ: A pointer to the environment array
 * @env_changed: An integer indicating if the environment has changed
 * @status: An integer representing the status
 * @cmd_buf: A pointer to the command chain buffer
 * @cmd_buf_type: An integer representing the command type
 * @readfd: An integer representing the read file descriptor
 * @histcount: An integer representing the history count
 */
typedef struct passinfo
{
char *arg;
char **argv;
char *path;
int argc;
unsigned int line_count;
int err_num;
int linecount_flag;
char *fname;
list_t *env;
list_t *history;
list_t *alias;
char **environ;
int env_changed;
int status;

char **cmd_buf; /* Pointer for memory management,to command chain buffer */
int cmd_buf_type; /* Command type: CMD_OR, CMD_NORMAL, CMD_AND */
int readfd;
int histcount;
} info_t;

#define INFO_INIT                           \
{                                       \
NULL, NULL, NULL, 0, 0, 0, 0, NULL, \
NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0                             \
}

/**
 * struct builtin - A structure for built-in commands
 * @type: A pointer to a string representing the type
 * @func: A function pointer to the corresponding built-in function
 */
typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;

/* Function Prototypes */

/* M_system_loop */
void fork_command(info_t *);
void find_command(info_t *);
int find_builtin_command(info_t *);
int shell_loop(info_t *, char **);

/* M_command_Parsing */
char *find_command_path(info_t *, char *, char *);
int is_command(info_t *, char *);
char *duplicate_characters(char *, int, int);

/* M_Shell_Loop */
int m_shell_loop(char **);

/* M_error_handling */
int write_string_to_fd(char *str, int fd);
int display_error_character(char);
int write_to_fd(char c, int fd);
void display_error(char *);

/* M_string_manipulation */
int string_length(char *);
int compare_strings(char *, char *);
char *starts_with_substring(const char *, const char *);
char *concatenate_strings(char *, char *);

/* M_String_Operations */
char *duplicate_string(const char *);
char *copy_string(char *, char *);
int write_character(char);
void display_string(char *);

/* M_exit_Handling */
char *copy_n_characters(char *, char *, int);
char *concatenate_n_characters(char *, char *, int);
char *find_character(char *, char);

/* M_tokenization */
char **tokenize_string(char *, char *);
char **tokenize_string_v2(char *, char);

/* M_memory_Operations */
char *set_memory(char *, char, unsigned int);
void free_memory(char **);
void *resize_memory(void *, unsigned int, unsigned int);
int free_block(void **);

/* M_numeric_Operations */
int convert_to_integer(char *);
int is_delimiter(char, char *);
int is_alpha(int);
int interactive_shell(info_t *);

/* M_error_handling_02 */
int display_integer(int, int);
void remove_comments_from_string(char *);
void display_custom_error(info_t *, char *);
int convert_error_to_integer(char *);
char *convert_integer_to_string(long int, int, int);

/* M_built_in_Commands */
int change_directory(info_t *);
int display_help(info_t *);
int exit_shell(info_t *);

/* M_built_in_Commands_02 */
int manage_alias(info_t *);
int display_history(info_t *);

/* M_input_handling */
ssize_t read_input(info_t *);
int read_line(info_t *, char **, size_t *);
void handle_sigint(int);

/* Information Management */
void set_shell_info(info_t *, char **);
void clear_shell_info(info_t *);
void free_shell_info(info_t *, int);


/* Environment-related functions */
char *get_environment_var(info_t *info, const char *name);
int display_environment(info_t *info);
int set_environment_var(info_t *info);
int unset_environment_var(info_t *info);
int populate_environment_list(info_t *info);

/* get environment-related */
char **environment_get(info_t *info);
int unset_variable_environment(info_t *info, char *name);
int set_variable_environment(info_t *info, char *name, char *value);

/* History-related functions */
char *history_filename(info_t *info);
int write_history_to_file(info_t *info);
int read_history_from_file(info_t *info);
int build_history_list(info_t *info, char *buffer, int line_count);
int renumber_history_list(info_t *info);

/* Linked list-related functions */
list_t *add_node_to_list(list_t **head, const char *str, int value);
list_t *add_node_to_list_end(list_t **head, const char *str, int value);
size_t print_string_list(const list_t *head);
int delete_node_at_index_from_list(list_t **head, unsigned int index);
void free_string_list(list_t **head);

/* Linked list-related functions (additional) */
size_t get_list_length(const list_t *head);
char **list_to_string_array(list_t *head);
size_t print_integer_list(const list_t *head);
list_t *find_node_starting_with(list_t *head, char *str, char c);
ssize_t get_node_index_in_list(list_t *head, list_t *node);

/* Variable-related functions */
int is_variable_chain(info_t *info, char *str, size_t *index);
void check_variable_chain(info_t *info, char *str, size_t *index, size_t start, size_t end);
int alias_replaced(info_t *info);
int variables_replace(info_t *info);
int replace_string_in_array(char **str_array, char *replacement);









#endif


