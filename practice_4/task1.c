#include <stdio.h>
int main()
{
    int szt = sizeof(size_t);
    float max=0;
    max = pow(2, szt*8);
    printf("sizeof size_t = %u; " 
            "max value of the param to malloc = %.0f\n", 
            szt, max);
    return 0;
}
