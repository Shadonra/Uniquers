#include <stdlib.h>
#include <time.h>
#include "rb.h"
#define UTILS_H 1

unsigned long min(unsigned long a, unsigned long b);
unsigned long max(unsigned long a, unsigned long b);

int trailing_zeroes(long l);
int compare_long (const void*, const void*, void*);
int reverse_compare_long(const void*, const void*, void*);
/* An implementation of a hash with (implicit) striped matrix. 
   This hash is 2-wise independent (2-universal)
*/
typedef struct hash_fn {
  long stripe[2];
  long offset;
  
  void init() {
    init(time(NULL));
  } 
  void init(int seed) {
    for(int i = 0; i < 2; i++) {
      int l = rand();
      int r = rand();
      stripe[i] = ((long) l) << 32;
      stripe[i] = stripe[i] ^ ((long) r);
    }
    offset = ((long) rand()) << 32;
    offset = offset ^ ((long) rand());
    
  }
  unsigned long parity(unsigned long x) {
    int size = sizeof(long) * 4;
    unsigned long parity = x;
    while(size > 0) {
      parity = parity ^ (parity << size);
      size /= 2;
    }
    return (parity & ((unsigned long) 1l << 63));
  }

  unsigned long hash(unsigned long key) {
    unsigned long ret = 0;
    long mask = 1l << 63;
    ret = ret | parity(key & stripe[0]);
    for(unsigned int i = 1; i < sizeof(long) * 8; i++) {
      unsigned long overfill = (~mask) & ((key >> i) & stripe[1]);
      unsigned long rest = mask & ((key << (sizeof(long) * 8 - i)) & stripe[0]);
      ret = ret | ((parity(overfill) ^ parity(rest)) >> i);
      mask = mask >> 1;
    }
    return ret ^ offset;
  }
} hash_fn;

