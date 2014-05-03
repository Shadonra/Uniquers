#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "alg_1.h"
#include "alg_2.h"
#include "alg_3.h"
#include "rb.h"
#define IN_BUF_SIZE 134217728
const double EPSILON = (1.0/32.0);
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

    struct rb_table *small_values = rb_create(compare_long, NULL, NULL);
    unsigned int tree_size = (unsigned int) ceil(96 / (EPSILON * EPSILON));
    struct rb_traverser sv_trav;
    rb_t_init(&sv_trav, small_values);
    //paper says to use this size

    size_t longs_read;
    unsigned long total = 0;
    unsigned long* in_buf = (unsigned long*) malloc(IN_BUF_SIZE * sizeof(long));
    while((longs_read = fread(in_buf, sizeof(long), IN_BUF_SIZE, infile)) != 0) {
      estimate_1(longs_read, in_buf, EPSILON, small_values, &sv_trav, hash);
    }
    printf("%d %lu %lu\n", small_values->rb_count, *(unsigned long*)(rb_t_last(&sv_trav, small_values)), 1l<<64);
    printf("%ld unique elements\n", ((long)small_values->rb_count) * 
      (((unsigned long) (~0l)) / 
        (*(unsigned long*)(rb_t_last(&sv_trav, small_values)))));
    free(in_buf);

  } else if (algorithm_number == 2) {
    int i;
    size_t num_hashes = 1.0 / (EPSILON * EPSILON);
    hash_fn **hashes = (hash_fn**) malloc(sizeof(hash_fn*) * num_hashes);
    for(i = 0; i < num_hashes; i++) {
      hashes[i] = (hash_fn*) malloc(sizeof(hash_fn));
      (hashes[i])->init(time(NULL) + i);
      printf("%x%x\n", hashes[i]->stripe[0], hashes[i]->stripe[1]);
    }
    hash_fn hll_hash;
    hll_hash.init();
    
    size_t longs_read;
    unsigned long* in_buf = (unsigned long*) malloc(IN_BUF_SIZE * sizeof(long));
    int r = 0;
    while((longs_read = fread(in_buf, sizeof(long), IN_BUF_SIZE, infile)) != 0) {
      r = max(r, hyper_log_log(longs_read, in_buf, hll_hash));
      printf("%d\n", r);
    }
    rewind(infile);
    long mask = (1l << 63) >> (63 - r);
    printf("%lx\n", ~mask);
    while((longs_read = fread(in_buf, sizeof(long), IN_BUF_SIZE, infile)) != 0) {
      estimate_2(longs_read, in_buf, ~mask, num_hashes, hashes);
      printf("got here\n");
    }
    int counter = 0;
    for(i = 0; i < num_hashes; i++) {
      if(hashes[i] == NULL) {
        counter++;
      }
    }
    printf("%d %d  %d\n", counter, num_hashes, r);
    printf("%ld\n", (long) ((log(1.0 - (((double)counter)/(double)num_hashes)))/log(1.0 - (1.0/((double (1 << r)))))));
    
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
    
    size_t longs_read;
    unsigned long* in_buf = (unsigned long*) malloc(IN_BUF_SIZE * sizeof(long));
    unsigned int *t = (unsigned int*) malloc(sizeof(int));
    *t = 0;
    unsigned int *buf_elements = (unsigned int*) malloc(sizeof(int));
    *buf_elements = 0;
    while((longs_read = fread(in_buf, sizeof(long), IN_BUF_SIZE, infile)) != 0) {
      estimate_3(longs_read, in_buf, EPSILON, h, g, buffer, t, buf_elements);
    }
    printf("%d unique elements\n", *buf_elements * (1 << (*t)));
  } else {
    printf("Invalid number, use either 1, 2, or 3\n");
  }
}
