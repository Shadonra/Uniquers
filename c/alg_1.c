#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "alg_1.h"

/* Let arr be a list of numbers.
 * Pick a random hash function  h : [m] \rightarrow [0, 1].
 * Apply h to each number in arr, keeping track of the t = 1/(\epsilon ^ 2) elements which map to the smallest values
 * Let v be the largest such value, and estimate the number of unique elements in arr to be F_0 = t / v
 */


void estimate_1 (size_t arr_size, unsigned long *arr, double epsilon, struct rb_table *small_values, struct rb_traverser *sv_trav, hash_fn hash) {
  size_t tree_size = (unsigned int) (ceil(96.0 / (epsilon * epsilon)));
  int i;
  unsigned long *last;
  for(i = 0; i < arr_size; i++) {
    unsigned long *hash_val = (unsigned long*) malloc(sizeof(long));
    *hash_val = hash.hash(arr[i]);
    
    if(rb_find(small_values, hash_val)) { //ignore repeats
      free(hash_val);
      continue;
    
    } else if(small_values->rb_count < tree_size) { //if tree's not full yet, stuff it
      rb_insert(small_values, hash_val);
    
    } else if(last && *hash_val < *last) { //keep the |tree_size| smallest vals
      rb_delete(small_values, last);
      rb_insert(small_values, hash_val);
    
    } else free(hash_val); 

    last = (unsigned long*) rb_t_last(sv_trav, small_values);
  }
}
