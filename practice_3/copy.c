#include <stdio.h>

#define MAX_SIZE 104857600

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Program need two arguments\n");
        return 1;
    }
    FILE *f1 = fopen(argv[1], "rb");
    if (!f1) {
        printf("Cannot open file %s for reading\n", argv[1]);
        return 1;
    }
    if (fseek(f1, 0, SEEK_END) != 0) return 1;
    long sz = ftell(f1);
    if (sz < 0 || sz > MAX_SIZE) {
        printf("File size exceeds limit of %d bytes\n", MAX_SIZE);
        fclose(f1);
        return 1;
    }
    rewind(f1);
    FILE *f2 = fopen(argv[2], "wb");
    if (!f2) {
        printf("Cannot open file %s for writing\n", argv[2]);
        fclose(f1);
        return 1;
    }
    char buf[4096];
    size_t r;
    while ((r = fread(buf, 1, sizeof(buf), f1)) > 0)
        if (fwrite(buf, 1, r, f2) != r) return 1;
    fclose(f1);
    fclose(f2);
}
