#include "utils.h"

int compare_long(const void *rb_a, const void *rb_b, void *rb_param) {
  if ((*(unsigned long*)rb_a) < (*(unsigned long*)rb_b)) {
    return -1;
  } else if ((*(unsigned long*) rb_a) == (*(unsigned long*)rb_b)) {
    return 0;
  } else {
    return 1;
  }
}

int reverse_compare_long(const void *rb_a, const void *rb_b, void *rb_param) {
  return -compare_long(rb_a, rb_b, rb_param);
}
unsigned long min (unsigned long a, unsigned long b) {
  return (a < b) ? a : b;
}

unsigned long max(unsigned long a, unsigned long b) {
  return (a > b) ? a : b;
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
  


