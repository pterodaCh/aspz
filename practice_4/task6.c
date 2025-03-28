#include <stdio.h>
#include <stdlib.h>

int main() 
{
    printf("realloc(NULL, 10)\n");

    int* ptr1 = realloc(NULL, 10 * sizeof(int));
    if (ptr1) 
    {
        printf("Success: ptr1 = %p, memory allocated\n", (void*)ptr1);
        free(ptr1);
    } else 
    {
        printf("Memory allocation failed\n");
    }

    printf("realloc(ptr, 0)\n");

    int* ptr2 = malloc(20 * sizeof(int));
    if (!ptr2) 
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("memory1: %p\n", (void*)ptr2);

    ptr2 = realloc(ptr2, 0);
    if (!ptr2) 
    {
        printf("Memory freed\n");
    }

    return 0;
}
