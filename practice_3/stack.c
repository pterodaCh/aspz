#include <stdio.h>

void recursive_function(int count) {
    printf("Recursion depth: %d\n", count);
    recursive_function(count + 1);
}

int main() {
    recursive_function(1);
    return 0;
}
