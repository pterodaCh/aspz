#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <limits.h>

#define MAX_SHELLS 10
const char *standard_shells[MAX_SHELLS] = {
    "/bin/sh",
    "/bin/csh",
    "/bin/tcsh",
};

// Перевіряє, чи шлях до exe є стандартним шелом
int is_standard_shell(const char *exe_path) {
    for (int i = 0; i < MAX_SHELLS; i++) {
        if (standard_shells[i] && strcmp(exe_path, standard_shells[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Отримати шлях до виконуваного файлу процесу
int get_exe_path(pid_t pid, char *exe_path, size_t size) {
    char proc_path[PATH_MAX];
    snprintf(proc_path, sizeof(proc_path), "/proc/%d/file", pid);
    ssize_t len = readlink(proc_path, exe_path, size - 1);
    if (len < 0) return -1;
    exe_path[len] = '\0';
    return 0;
}

int main() {
    DIR *proc = opendir("/proc");
    if (!proc) {
        perror("opendir /proc");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(proc)) != NULL) {
        if (!isdigit(entry->d_name[0])) continue;

        pid_t pid = atoi(entry->d_name);
        char exe_path[PATH_MAX];

        if (get_exe_path(pid, exe_path, sizeof(exe_path)) == 0) {
            if (!is_standard_shell(exe_path)) {
                printf("PID: %d\tEXE: %s\n", pid, exe_path);
            }
        }
    }

    closedir(proc);
    return 0;
}
