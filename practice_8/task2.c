
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    const char *filename = "task2.bin";
    unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    unsigned char buffer[4];
  
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);

    write(fd, data, sizeof(data));
    close(fd);

    fd = open(filename, O_RDONLY);
    lseek(fd, 3, SEEK_SET);
    ssize_t bytesRead = read(fd, buffer, 4);

    printf("Buffer contents: ");
    for (int i = 0; i < bytesRead; ++i) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    close(fd);
    return 0;
}
