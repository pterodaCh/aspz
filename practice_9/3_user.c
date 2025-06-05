
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *file = "/home/ptero/backup.txt";

    FILE *fp = fopen(file, "a");
    if (!fp) {
        perror("fopen");
    } else {
        fprintf(fp, "Appending line as user.\n");
        fclose(fp);
        printf("File modified.\n");
    }


    if (remove(file) != 0) {
        perror("remove");
    } else {
        printf("File deleted.\n");
    }

    return 0;
}
