#include <stdio.h>
#include <stdlib.h>

#define MAX_LINES 3        // Number of lines to print
#define BUFFER_SIZE 1024   // Maximum length of a line

/*
 * Function: main
 * --------------
 * Reads a file and prints up to the first MAX_LINES lines.
 *
 * input: argc - argument count, argv - array of command-line arguments
 * output: prints file contents to stdout; errors to stderr
 * returns: 0 on success, 1 on failure
 */
int main(int argc, char **argv) {
    if (argc == 1) {
        fprintf(stderr, "Error: No file provided\n");
        return 1;
    }

    if (argc > 2) {
        fprintf(stderr, "Error: Too many files\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror(argv[1]);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    int line_count = 0;

    while (fgets(buffer, sizeof(buffer), fp) != NULL && line_count < MAX_LINES) {
        fputs(buffer, stdout);
        line_count++;
    }

    fclose(fp);
    return 0;
}