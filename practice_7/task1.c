#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char buffer[1024];

    fp = popen("more", "w");
    if (fp == NULL) {
        perror("popen failed");
        return 1;
    }

    FILE *rwho_fp = popen("rwho", "r");
    if (rwho_fp == NULL) {
        perror("popen rwho failed");
        pclose(fp);
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), rwho_fp) != NULL) {
        fputs(buffer, fp);
    }

    pclose(rwho_fp);
    pclose(fp);

    return 0;
}
