#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        printf("pid %d\n", getpid());
        printf("pid parent process: %d\n", getppid());
        exit(0);
    } else {
        wait(NULL);
    }

    return 0;
}
