#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "alg_1.h"
#include "alg_3.h"

#define IN_BUF_SIZE 134217728
#define EPSILON (1.0/256.0)
//extern void estimate_1(long arr_size, long* arr, double epsilon, heap small_values, hash_fn hash);

int main(int argc, char *argv[]) {
  if(argc != 3) {
    printf("Usage: %s <algorithm number> <infile>\n", argv[0]);
    return 1;
  }

  int algorithm_number = atoi(argv[1]);
  FILE* infile = fopen(argv[2], "r");
  if(algorithm_number == 1) { 
    hash_fn hash;
    hash.init();

    heap small_values;
    unsigned int heap_size = (unsigned int) ceil(96 * 20 * 20); //paper says to use this number
    printf("%ld\n", (long)heap_size);
    small_values.init(heap_size);

    size_t bytes_read;
    unsigned long total = 0;
    long* in_buf = (long*) malloc(IN_BUF_SIZE * sizeof(long));
    while((bytes_read = fread(in_buf, sizeof(long), IN_BUF_SIZE, infile)) != 0) {
      estimate_1(bytes_read / sizeof(long), in_buf, 1.0/20.0, &small_values, hash);
      printf("%ld %ld\n", total += bytes_read, small_values.peek());
    }
    printf("%ld\n", ((long) heap_size) * (((unsigned long) 1l << 63) / small_values.peek()));
    free(in_buf);
  } else if (algorithm_number == 2) {

  } else if (algorithm_number == 3) {
    int i;
    struct rb_table **buffer = (struct rb_table **) malloc(sizeof(struct rb_table *) * 65);
    for(i = 0; i < 65; i++) {
      buffer[i] = rb_create(compare_long, NULL, NULL);
    }
    hash_fn h;
    hash_fn g;
    h.init();
    g.init();
    
    size_t bytes_read;
    unsigned long* in_buf = (unsigned long*) malloc(IN_BUF_SIZE * sizeof(long));
    int *t = (int*) malloc(sizeof(int));
    *t = 0;
    int *buf_elements = (int*) malloc(sizeof(int));
    *buf_elements = 0;
    while((bytes_read = fread(in_buf, sizeof(long), IN_BUF_SIZE, infile)) != 0) {
      estimate_3(bytes_read / sizeof(long), in_buf, 1.0/20.0, h, g, buffer, t, buf_elements);
    }
    printf("%ld\n", (long)buf_elements * (long)pow(2, (double)*t));
  } else {
    printf("Invalid number, use either 1, 2, or 3\n");
  }
}
