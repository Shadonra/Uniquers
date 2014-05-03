#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
int main() {
  hash_fn hash;
  hash.init();
  printf("%lx %lx\n", hash.stripe[0], hash.stripe[1]);
  for(int i = 0; i < 32; i++) {
    printf("%lx\n", hash.hash((unsigned long)i));
  }
}
