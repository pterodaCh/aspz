#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int contains(int *arr, int size, int num) {
    for (int i = 0; i < size; i++)
        if (arr[i] == num) return 1;
    return 0;
}

int main() {
    srand(time(NULL));

    int lotto49[7];
    int lotto36[6];

    int count = 0;
    while (count < 7) {
        int num = rand() % 49 + 1;
        if (!contains(lotto49, count, num)) {
            lotto49[count++] = num;
        }
    }

    count = 0;
    while (count < 6) {
        int num = rand() % 36 + 1;
        if (!contains(lotto36, count, num)) {
            lotto36[count++] = num;
        }
    }

    printf("(7, 49): ");
    for (int i = 0; i < 7; i++) printf("%d ", lotto49[i]);
    printf("\n");

    printf("(6, 36): ");
    for (int i = 0; i < 6; i++) printf("%d ", lotto36[i]);
    printf("\n");
    while(1);
    return 0;
}
