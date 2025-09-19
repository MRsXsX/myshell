/*********************************************************************
 * Author: Your Name
 * Created: September 18, 2025
 *
 * myshell.c
 * A simple Unix-like shell implementation for class assignment.
 * 
 * Features:
 *  - Interactive prompt "myshell> "
 *  - Executes local programs using fork() and execvp()
 *  - Built-in "exit" command to terminate shell
 *  - Supports output redirection using "-o filename"
 * 
 * Design:
 *  - The shell reads a line of input using getline()
 *  - Splits input into arguments, checking for "-o" flag
 *  - Forks a child process that executes the requested command
 *  - Parent waits for child to complete, then re-prompts
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_ARGS 64        // Maximum number of arguments supported
#define MAX_LINE 1024      // Maximum length of input line

/*
 * Function: main
 * --------------
 *  Runs an interactive shell loop until the user types "exit".
 *
 *  input: none
 *  output: returns 0 when shell exits
 */
int main(void) {
    char *line = NULL;
    size_t len = 0;

    while (1) {
        printf("myshell> ");
        fflush(stdout);

        ssize_t nread = getline(&line, &len, stdin);
        if (nread == -1) {
            // EOF (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove trailing newline
        if (line[nread - 1] == '\n') {
            line[nread - 1] = '\0';
        }

        // Exit condition
        if (strcmp(line, "exit") == 0) {
            break;
        }

        // Parse input into arguments
        char *args[MAX_ARGS];
int arg_count = 0;
char *output_file = NULL;
int o_encountered = 0;

char *token = strtok(line, " ");
while (token != NULL && arg_count < MAX_ARGS - 1) {
    if (strcmp(token, "-o") == 0) {
        o_encountered = 1;
        token = strtok(NULL, " ");
        if (token == NULL) {
            fprintf(stderr, "Error: no output file specified after -o\n");
            break;
        }
        if (output_file != NULL) {
            fprintf(stderr, "Error: multiple output files specified\n");
            break;
        }
        output_file = token;
    } else {
        args[arg_count++] = token;
    }
    token = strtok(NULL, " ");
}
if (o_encountered && output_file == NULL) {
    continue;
}
        args[arg_count] = NULL;

        if (arg_count == 0) {
            // Empty command (just hit Enter)
            continue;
        }

        // Fork and execute
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork failed");
            continue;
        }

        if (pid == 0) {
            // Child process
            if (output_file != NULL) {
                int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1) {
                    perror("open failed");
                    exit(EXIT_FAILURE);
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }
            execvp(args[0], args);
            perror("execvp failed");
            exit(EXIT_FAILURE);
        } else {
            // Parent waits
            int status;
            waitpid(pid, &status, 0);
        }

 
    }

    free(line);
    return 0;
}
