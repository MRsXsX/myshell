/*********************************************************************
 * Author: Oleksii Kondratiuk
 * Created: September 15, 2025
 *
 * myuniq.c
 * --------
 * Prints unique adjacent lines from a file.
 * Optionally, use "-c" to print the count of each unique line.
 
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024  // maximum length of a line

int main(int argc, char **argv) {
    if (argc < 2 || argc > 3|| (argc == 2 && strcmp(argv[1], "-c") == 0)) {
        fprintf(stderr, "Usage: %s [-c] filename\n", argv[0]);
        return 1;
    }

    int use_count = 0;
    char *filename;
    
    if (argc == 3) {
        if (strcmp(argv[1], "-c") != 0) {
            fprintf(stderr, "Error: unknown option %s\n", argv[1]);
            return 1;
        }
        use_count = 1;
        filename = argv[2];
    } else {
        filename = argv[1];
    }

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror(filename);
        return 1;
    }

    char prev[BUFFER_SIZE];
    char curr[BUFFER_SIZE];

    if (fgets(prev, sizeof(prev), fp) == NULL) {
        // empty file
        fclose(fp);
        return 0;
    }

    int count = 1;
    while (fgets(curr, sizeof(curr), fp) != NULL) {
        if (strcmp(curr, prev) == 0) {
            count++;
        } else {
            if (use_count) {
                printf("%d %s", count, prev);
            } else {
                printf("%s", prev);
            }
            strcpy(prev, curr);
            count = 1;
        }
    }

    // print last line
    if (use_count) {
        printf("%d %s", count, prev);
    } else {
        printf("%s", prev);
    }

    fclose(fp);
    return 0;
}
