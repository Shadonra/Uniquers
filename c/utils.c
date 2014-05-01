#include "utils.h"

unsigned long min (unsigned long a, unsigned long b) {
  return (a < b) ? a : b;
}

unsigned long max(unsigned long a, unsigned long b) {
  return (a < b) ? a : b;
}

int trailing_zeroes(long l) {
  if(l == 0) return 64;
  int last_one = (~l + 1) & l;
  int i = 0;
  while(last_one > 1) {
    last_one /= 2;
    i++;
  }
  return i;
}
  


