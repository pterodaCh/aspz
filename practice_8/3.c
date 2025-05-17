
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct {
    char* name;
    int comparisons;
    double time_spent;
    int size;
} SortStats;

int comparison_count = 0;

int compare_ints(const void* a, const void* b) {
    comparison_count++;
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

void generate_sorted_array(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
}

void generate_reverse_sorted_array(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i - 1;
    }
}

void generate_equal_elements_array(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = 42;
    }
}

void generate_random_array(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
}

void generate_pattern_array(int* arr, int n) {
    int step = n / 4;
    for (int i = 0; i < n; i++) {
        if (i % step == 0) {
            arr[i] = 0;
        } else {
            arr[i] = i;
        }
    }
}

void generate_pivot_worst_case(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = (i % 2 == 0) ? 0 : 1000;
    }
}

void generate_organpipe_array(int* arr, int n) {
    int mid = n / 2;
    for (int i = 0; i < mid; i++) {
        arr[i] = i;
    }
    for (int i = mid; i < n; i++) {
        arr[i] = n - i - 1;
    }
}

void generate_few_unique_array(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = (i % 10);
    }
}

void copy_array(int* src, int* dest, int n) {
    memcpy(dest, src, n * sizeof(int));
}

bool is_sorted(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i-1]) {
            return false;
        }
    }
    return true;
}

SortStats run_sorting_experiment(int* arr, int n, char* name) {
    int* test_arr = (int*)malloc(n * sizeof(int));
    if (!test_arr) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    
    copy_array(arr, test_arr, n);
    
    comparison_count = 0;
    clock_t start = clock();
    qsort(test_arr, n, sizeof(int), compare_ints);
    clock_t end = clock();
    
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    SortStats stats;
    stats.name = name;
    stats.comparisons = comparison_count;
    stats.time_spent = time_spent;
    stats.size = n;
    
    if (!is_sorted(test_arr, n)) {
        printf("Eroor:  %s was not sorted correctly!\n", name);
    }
    
    free(test_arr);
    return stats;
}

void print_stats(SortStats* stats, int count) {
    printf("\n%-25s | %-12s | %-12s | %-15s\n", "Array type", "Size", "Time (s)", "Comparisons");

    
    for (int i = 0; i < count; i++) {
        printf("%-25s | %-12d | %-12.6f | %-15d\n", 
               stats[i].name, stats[i].size, stats[i].time_spent, stats[i].comparisons);
    }
    
    int worst_idx = 0;
    for (int i = 1; i < count; i++) {
        if (stats[i].comparisons > stats[worst_idx].comparisons) {
            worst_idx = i;
        }
    }
    
    printf("\nWorst case by comparisons: %s with %d comparisons\n", 
           stats[worst_idx].name, stats[worst_idx].comparisons);
    
    worst_idx = 0;
    for (int i = 1; i < count; i++) {
        if (stats[i].time_spent > stats[worst_idx].time_spent) {
            worst_idx = i;
        }
    }
    
    printf("Worst case by execution time: %s with %f seconds\n", 
           stats[worst_idx].name, stats[worst_idx].time_spent);
}

void validate_qsort() {
    printf("\n=== Validating qsort correctness ===\n");
    
    {
        int arr[] = {};
        int n = 0;
        qsort(arr, n, sizeof(int), compare_ints);
        printf("Test 1 (Empty array): Passed\n");
    }
    
    {
        int arr[] = {42};
        int n = 1;
        qsort(arr, n, sizeof(int), compare_ints);
        if (arr[0] == 42) {
            printf("Test 2 (Single element): Passed\n");
        } else {
            printf("Test 2 (Single element): Failed!\n");
        }
    }
    
    {
        int arr[] = {10, 5};
        int n = 2;
        qsort(arr, n, sizeof(int), compare_ints);
        if (arr[0] == 5 && arr[1] == 10) {
            printf("Test 3 (Two unordered elements): Passed\n");
        } else {
            printf("Test 3 (Two unordered elements): Failed!\n");
        }
    }
    
    {
        int arr[] = {1, 2, 3, 4, 5};
        int expected[] = {1, 2, 3, 4, 5};
        int n = 5;
        qsort(arr, n, sizeof(int), compare_ints);
        bool passed = true;
        for (int i = 0; i < n; i++) {
            if (arr[i] != expected[i]) {
                passed = false;
                break;
            }
        }
        if (passed) {
            printf("Test 4 (Sorted array): Passed\n");
        } else {
            printf("Test 4 (Sorted array): Failed!\n");
        }
    }
    
    {
        int arr[] = {5, 4, 3, 2, 1};
        int expected[] = {1, 2, 3, 4, 5};
        int n = 5;
        qsort(arr, n, sizeof(int), compare_ints);
        bool passed = true;
        for (int i = 0; i < n; i++) {
            if (arr[i] != expected[i]) {
                passed = false;
                break;
            }
        }
        if (passed) {
            printf("Test 5 (Reverse sorted array): Passed\n");
        } else {
            printf("Test 5 (Reverse sorted array): Failed!\n");
        }
    }
    
    {
        int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
        int expected[] = {1, 1, 2, 3, 4, 5, 5, 6, 9};
        int n = 9;
        qsort(arr, n, sizeof(int), compare_ints);
        bool passed = true;
        for (int i = 0; i < n; i++) {
            if (arr[i] != expected[i]) {
                passed = false;
                break;
            }
        }
        if (passed) {
            printf("Test 6 (Array with duplicates): Passed\n");
        } else {
            printf("Test 6 (Array with duplicates): Failed!\n");
        }
    }
    
    {
        int arr[] = {42, 42, 42, 42, 42};
        int expected[] = {42, 42, 42, 42, 42};
        int n = 5;
        qsort(arr, n, sizeof(int), compare_ints);
        bool passed = true;
        for (int i = 0; i < n; i++) {
            if (arr[i] != expected[i]) {
                passed = false;
                break;
            }
        }
        if (passed) {
            printf("Test 7 (Array with identical elements): Passed\n");
        } else {
            printf("Test 7 (Array with identical elements): Failed!\n");
        }
    }
    
    {
        int n = 1000;
        int* arr = (int*)malloc(n * sizeof(int));
        if (!arr) {
            fprintf(stderr, "Memory allocation error\n");
            return;
        }
        
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 10000;
        }
        
        qsort(arr, n, sizeof(int), compare_ints);
        bool passed = is_sorted(arr, n);
        
        if (passed) {
            printf("Test 8 (Large random array): Passed\n");
        } else {
            printf("Test 8 (Large random array): Failed!\n");
        }
        
        free(arr);
    }
}

int main() {
    srand(time(NULL));
    
    const int test_sizes[] = {100, 1000, 10000, 100000};
    const int num_sizes = sizeof(test_sizes) / sizeof(test_sizes[0]);
    const int num_test_types = 8;
    
    printf("Investigating worst case scenarios for qsort\n");

    
    for (int s = 0; s < num_sizes; s++) {
        int size = test_sizes[s];
        printf("\nArray size: %d\n", size);

        
        int* original_array = (int*)malloc(size * sizeof(int));
        if (!original_array) {
            fprintf(stderr, "Memory allocation error\n");
            return EXIT_FAILURE;
        }
        
        SortStats stats[num_test_types];
        
        generate_sorted_array(original_array, size);
        stats[0] = run_sorting_experiment(original_array, size, "Sorted");
        
        generate_reverse_sorted_array(original_array, size);
        stats[1] = run_sorting_experiment(original_array, size, "Reverse sorted");
        
        generate_equal_elements_array(original_array, size);
        stats[2] = run_sorting_experiment(original_array, size, "Equal elements");
        
        generate_random_array(original_array, size);
        stats[3] = run_sorting_experiment(original_array, size, "Random");
        
        generate_pattern_array(original_array, size);
        stats[4] = run_sorting_experiment(original_array, size, "Pattern");
        
        generate_pivot_worst_case(original_array, size);
        stats[5] = run_sorting_experiment(original_array, size, "Bad pivot");
        
        generate_organpipe_array(original_array, size);
        stats[6] = run_sorting_experiment(original_array, size, "Organpipe");
        
        generate_few_unique_array(original_array, size);
        stats[7] = run_sorting_experiment(original_array, size, "Many duplicates");
        
        print_stats(stats, num_test_types);
        
        free(original_array);
    }
    
    validate_qsort();
    
    return 0;
}
