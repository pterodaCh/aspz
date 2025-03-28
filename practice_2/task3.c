#include <stdio. h>
#include <stdlib. h>

int a = 1;
static int b = 2;

void func() {}

int main() 
{  
  int local_var;
  int *heap_var = malloc(sizeof (int));
  
  printf ("Text segment (func): %p\n", (void*) func);
  printf ("Data segment (global):  %p\n", (void*) &a) ;
  printf ("Data segment (static):  %p\n", (void*) &b) ;
  printf ("Heap segment: %p\n", (void*) &b) ;
  printf ("Stack top: %p\n", (void*) &local_var);
  
  free (heap_var);
  return 0;
}  

  

  
