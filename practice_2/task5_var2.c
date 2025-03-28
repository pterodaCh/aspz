#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>

#define ITERATIONS 1000000
#define BLOCK_SIZE 1024

void test_malloc()
 {
  clock_t start, end;
  double cpu_time_used;
  start = clock();
  for (int i = 0; i < ITERATIONS; i++)
  {
    void *ptr = malloc (BLOCK_SIZE);
    free(ptr);
  }  

  end = clock() ;
cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
printf("Malloc()/free(): %f seconds\n", cpu_time_used);

}

void test_mmap( )
{
  clock_t start, end;
  double cpu_time_used;
  start = clock();
  for (int i = 0; i < ITERATIONS; i++)
  {  
    void *ptr = mmap (NULL, BLOCK_SIZE, PROT_READ | PROT_WRITE,
      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    munmap (ptr, BLOCK_SIZE) ;
  }
  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("mmap()/munmap(): %f seconds\n", cpu_time_used);
}

void compare_memory_usage()
{
  long page_size = sysconf(_SC_PAGE_SIZE);
  printf("System page size: %ld bytes\n", page_size);
}

int main()
{
  printf("Comparing memory allocation:\n");
  compare_memory_usage();
  test_malloc();
  test_mmap();
  return 0;
}
