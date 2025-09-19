#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024  // Maximum line 

/*
 * mycat
 * -----
 * Concatenate the contents of one or two files and print to stdout.
 * Fails immediately if any file cannot be opened.
 */
int main(int argc, char **argv) {
    if (argc == 1) {
        fprintf(stderr, "Usage: %s file1 [file2]\n", argv[0]);
        return 1;
    }

    if (argc > 3) {
        fprintf(stderr, "Error: Too many files provided (max 2 allowed)\n");
        return 1;
    }

    char buffer[BUFFER_SIZE];

    // If two files, check both exist before printing anything
    if (argc == 3) {
        FILE *fp1 = fopen(argv[1], "r");
        FILE *fp2 = fopen(argv[2], "r");
        if (!fp1) {
            perror(argv[1]);
            return 1;
        }
        if (!fp2) {
            perror(argv[2]);
            fclose(fp1);
            return 1;
        }
        // Print first file
        while (fgets(buffer, sizeof(buffer), fp1) != NULL) {
            fputs(buffer, stdout);
        }
        fclose(fp1);
        // Print second file
        while (fgets(buffer, sizeof(buffer), fp2) != NULL) {
            fputs(buffer, stdout);
        }
        fclose(fp2);
    } else {
        FILE *fp = fopen(argv[1], "r");
        if (!fp) {
            perror(argv[1]);
            return 1;
        }
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            fputs(buffer, stdout);
        }
        fclose(fp);
    }

    return 0;
}
