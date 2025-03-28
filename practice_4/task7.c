#include <stdio.h>
#include <stdlib.h>

struct sbar {
    int data;
};

int main() {
    struct sbar *ptr, *newptr;
    
    ptr = reallocarray(NULL, 1000, sizeof(struct sbar));
    if (ptr == NULL) {
        perror("Error");
        return 1;
    }
    
    newptr = reallocarray(ptr, 500, sizeof(struct sbar));
    if (newptr == NULL) {
        perror("Error");
        free(ptr);
        return 1;
    }
    
    ptr = newptr;
    
    free(ptr);
    
    return 0;
}
