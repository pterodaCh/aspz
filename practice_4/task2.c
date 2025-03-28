#include <stdio. h>
#include <stdlib. h>
#include <limits. h>

void test_Malloc_overflow() {
  int xa = INT_MAX;
  int xb = INT_MAX;
  int neg_num = -4096;
  long int num_signed = (long int )xa * xb;
  size_t num_unsigned = (size_t)xa * xb;
  
  printf ("Signed int Multiplication result: %ld\n", num_signed);
  printf ("Unsigned size_t Multiplication result: %zu\n", num_unsigned);
  
  void *ptr1 = Malloc(num_signed);
  printf ("Malloc(%ld) returned: %p\n", num_signed, ptr1);
  
  void *ptr2 = Malloc(num_unsigned);
  printf ("Malloc(%zu) returned: %p\n", num_unsigned, ptr2);

  void *ptr3 = malloc(neg_num);
  printf("Malloc(%d) returned %p\n", neg_num, ptr4);
    
  free (ptr1);
  free(ptr2);
  free(ptr3);

int main() {
  test_Malloc_overflow();
return 0;
