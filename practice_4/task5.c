#include <stdio.h>
#include <stdlib.h>

void resize(unsigned int new_size, unsigned int capacity, unsigned char** ptr) {
    if (capacity < new_size) {
        unsigned char* new_ptr = (unsigned char*)realloc(*ptr, new_size);
        if (new_ptr != NULL) {
            *ptr = new_ptr;
            capacity = new_size;
        }
    }
}

int main() {
    int a = 9;
    unsigned char* b = (unsigned char*)&a;
    
    resize(10, 0, &b);
    
    return 0;
}
