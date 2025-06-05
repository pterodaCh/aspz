#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    const char *src = "/aspz/practice_9/original.txt";
    const char *copy = "/home/ptero/backup.txt";

    FILE *fp = fopen(src, "w");
    if (!fp) {
        perror("fopen (original)");
        return 1;
    }
    fprintf(fp, "This is the original file.\n");
    fclose(fp);

    char cmd[512];
    snprintf(cmd, sizeof(cmd), "cp %s /tmp/root_copy.txt", src);
    system(cmd);

    chown("/tmp/root_copy.txt", 0, 0);

    snprintf(cmd, sizeof(cmd), "cp /tmp/root_copy.txt %s", copy);
    system(cmd);

    printf("File copied to %s\n", copy);
    return 0;
}
