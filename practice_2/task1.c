#include <stdio. h>
#include <time. h>
#include <stdint. h>

int main() 
{
  time_t max_time_t;
  printf ("Word size: %zu\n", sizeof (void*) *8);
  
  #if UINTPTR_MAX == 0xFFFFFFFF
  max_time_t = (time_t)UINT32_MAX;
  #else
  max_time_t = (time_t)UINT64_MAX;
  #endif
  
  struct tm *tm_info;
  tm_info = localtime(&max_time_t);
  printf ("Max value time_t: %1ld\n", (long long)max_time_t);
  printf ("Date and time, when time_t ends: %s", asctime(tm_info));
  return 0;
}
