#ifndef MADIFORT_H
#define MADIFORT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Buffer sizes for reading and writing */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -vi

/* Constants for command chaining */
#define COMMAND_NORMAL 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3

/* Flags for convertToNumber() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* Flags for using system getline() and strtok() */
#define USEreadInput 0
#define USE_STRTOK 0

#define history_list_FILE
#define MAX_history_list_SIZE 4096

extern char **environment_listironment_variables;

/**
 * Structure for a singly linked list node.
 */
typedef struct ListNode
{
    int number;
    char *string;
    struct ListNode *next;
} LinkedListNode;

/**
 * Structure for passing pseudo-arguments to command_functiontions, ensuring a uniform protocommand_type for command_functiontion pointers.
 */
typedef struct ArgumentInfo
{
    char *argument_string;
    char **argument_array;
    char *command_command_path;
    int argument_count;
    unsigned int error_error_line_count;
    int error_number;
    int count_line_flag;
    char *file_name;
    LinkedListNode *environment_listironment_list;
    LinkedListNode *history_list_list;
    LinkedListNode *alias_list_list;
    char **modified_environment_listironment;
    int env_changed;
    int command_command_status;
    char **command_buffer;
    int command_buffer_command_type;
    int Read_fileD;
    int history_LC;
} Info;

#define INFO_INITZZ \
    {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
     0, 0, 0}

/**
 * Structure for built-in commands and their corresponding command_functiontions.
 */
typedef struct BuiltinCommandCommand
{
    char *command_command_type;
    int (*command_command_functiontion)(Info *);
} BuiltinCommandCommandTable;

/* command_functiontion declarations for shell loop operations */
int shellLoop(Info *, char **);
int findBuiltinCommand(Info *);
void findCommand(Info *);
void forkCommand(Info *);

/* command_functiontion declarations for parsing commands */
int isCommand(Info *, char *, size_t);
char *duplicateCharacters(char *, int, int);
char *findCommandcommand_path(Info *, char *);

/* Main loop command_functiontion */
int mainLoop(char **);

/* Error handling command_functiontions */
void displayErrorMessage(char *);
int displayErrorCharacter(char);
int putCharacterToFileDescriptor(char c, int fd);
int putStringToFileDescriptor(char *str, int fd);

/* String manipulation command_functiontions */
int stringLength(char *);
int stringCompare(char *, char *);
char *startsWith(const char *, const char *);
char *concatenateStrings(char *, char *);

/* String manipulation (part 2) command_functiontions */
char *copyString(char *, char *);
char *duplicateString(const char *);
void printString(char *);
int putCharacter(char);

/* command_functiontions related to exits */
char *copyStringN(char *, char *, int);
char *concatenateStringN(char *, char *, int);
char *findCharacter(char *, char);

/* Tokenization command_functiontions */
char **splitString(char *, char *);
char **splitString2(char *, char);

/* Memory reallocation command_functiontions */
char *setMemory(char *, char, unsigned int);
void freeMemory(char **);
void *reallocateMemory(void *, unsigned int, unsigned int);

/* Memory management command_functiontions */
int freeBlock(void **);

/* Atoi command_functiontions */
int handlehandleInteractiveModeMode(Info *);
int isDelimiter(char, char *);
int isAlphabetic(int);
int convertToInteger(char *);

/* More error handling command_functiontions */
int errorAtoi(char *);
void printError(Info *, char *);
int printInteger(int, int);
char *convertToNumber(long int, int, int);
void removeComments(char *);

/* Built-in command command_functiontions */
int exitShell(Info *);
int changeDirectory(Info *);
int displayHelp(Info *);

/* Built-in command (part 2) command_functiontions */
int displayhistory_list(Info *);
int handlealias_list(Info *);

/* Input handling command_functiontions */
ssize_t getInput(Info *);
int readInput(Info *, char **, size_t *);
void handleInterruptSignal(int);

/* Information retrieval command_functiontions */
void clearInformation(Info *);
void setInformation(Info *, char **);
void freeInformation(Info *, int);

/* environment_listironmental variable command_functiontions */
char *getenvironment_listironmentVariable(Info *, const char *);
int displayenvironment_listironment(Info *);
int setenvironment_listironmentVariable(Info *, char *, char *);
int unsetenvironment_listironmentVariable(Info *, char *);
int populateenvironment_listironmentList(Info *);

/* command_functiontions for getting environment_listironment variables */
char **getenvironment_listironment(Info *);
int unsetenvironment_listironmentVariable(Info *, char *);
int setenvironment_listironmentVariable(Info *, char *, char *);

/* history_list-related command_functiontions */
char *gethistory_listFileName(Info *info);
int writehistory_listToFile(Info *info);
int readhistory_listFromFile(Info *info);
int buildhistory_listList(Info *info, char *buffer, int lineCount);
int renumberhistory_list(Info *info);

/* Linked list command_functiontions */
LinkedListNode *addNode(LinkedListNode **, const char *, int);
LinkedListNode *addNodeEnd(LinkedListNode **, const char *, int);
size_t printListString(const LinkedListNode *);
int deleteNodeAtIndex(LinkedListNode **, unsigned int);
void freeLinkedList(LinkedListNode **);

/* Linked list (part 2) command_functiontions */
size_t getLinkedListLength(const LinkedListNode *);
char **convertListToStrings(LinkedListNode *);
size_t printLinkedList(const LinkedListNode *);
LinkedListNode *findNodeStartsWith(LinkedListNode *, char *, char);
ssize_t getNodeIndex(LinkedListNode *, LinkedListNode *);

/* Variable substitution command_functiontions */
int isCommandChain(Info *, char *, size_t *);
void checkCommandChain(Info *, char *, size_t *, size_t, size_t);
int replacealias_list(Info *);
int replaceVariables(Info *);
int substituteString(char **, char *);

#endif /* _SHELL_H_ */

