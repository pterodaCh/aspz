
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int is_directory_filter(const struct dirent *entry) {
    struct stat st;
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        return 0;
    if (stat(entry->d_name, &st) == -1)
        return 0;
    return S_ISDIR(st.st_mode);
}

int main(void)
{
    struct dirent **namelist;
    int n;

    n = scandir(".", &namelist, is_directory_filter, alphasort);
    if (n < 0)
        perror("scandir");
    else {
        for (int i = 0; i < n; i++) {
            printf("%s\n", namelist[i]->d_name);
            free(namelist[i]);
        }
        free(namelist);
    }
    return 0;
}
