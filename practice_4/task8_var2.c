#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char *str = malloc(20);
    strcpy(str, "hHello");
    printf("%s\n", str);
    return 0;
}
