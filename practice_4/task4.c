#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = NULL;
    for (int i = 0; i < 5; i++) {
        if (!ptr)
            ptr = malloc(10000*i); 

        if (ptr) {
            printf("Iteration %d: Using %s\n", i, ptr);
        }

        free(ptr);  
        //ptr = NUll;
    }

    return 0;
}
