#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Eroro: usage is %s searched word filename\n", argv[0]);
        return 1;
    }

    const char *word = argv[1];
    const char *filename = argv[2];
    char line[MAX_LINE];

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("open failed");
        return 1;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, word) != NULL) {
            printf("%s", line);
        }
    }

    fclose(fp);
    return 0;
}
