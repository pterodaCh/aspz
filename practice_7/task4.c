#include <stdio.h>
#include <stdlib.h>

#define LINES_PER_PAGE 20

void show_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror(filename);
        return;
    }

    char line[1024];
    int line_count = 0;

    while (fgets(line, sizeof(line), fp)) {
        fputs(line, stdout);
        line_count++;

        if (line_count == LINES_PER_PAGE) {
            printf("(ENTER)");
            while (getchar() != '\n');  
            line_count = 0;
        }
    }

    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (i != 1)
        {
            printf("--MORE--(END - Next: %s) \n", argv[i]);
        }

        show_file(argv[i]);
    }

    return 0;
}
