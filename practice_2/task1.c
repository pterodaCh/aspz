#include <stdio. h>
#include <time. h>
#include <stdint. h>

int main() 
{
  time_t max_time_t;
  printf ("Word size: %zu\n", sizeof (void*) *8);
  
  time_t max_time_t = (time_t)((1ULL << (sizeof(time_t) * 8 - 1)) - 1);

  
  struct tm *tm_info;
  tm_info = localtime(&max_time_t);
  printf ("Max value time_t: %1ld\n", (long long)max_time_t);
  printf ("Date and time, when time_t ends: %s", asctime(tm_info));
  return 0;
}
