#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int flags = fcntl(pipefd[1], F_GETFL);
    fcntl(pipefd[1], F_SETFL, flags | O_NONBLOCK);


    size_t size = 1 << 20; 
    char *buffer = malloc(size);
    memset(buffer, 'A', size);

    ssize_t written = write(pipefd[1], buffer, size);
    if (written == -1) {
        perror("write");
    } else {
        printf("Requested to write %zu bytes, actually wrote %zd bytes\n", size, written);
    }

    free(buffer);
    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}
