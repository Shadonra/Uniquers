#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "heap.h"
/* Let arr be a list of numbers.
 * Pick a random hash function  h : [m] \rightarrow [0, 1].
 * Apply h to each number in arr, keeping track of the t = 1/(\epsilon ^ 2) elements which map to the smallest values
 * Let v be the largest such value, and estimate the number of unique elements in arr to be F_0 = t / v
 */

int estimate_1 (long arr_size, long *arr, double epsilon) {
  heap small_values; //max-heap - paper says to use binary search tree, but a heap will work
  long i;
  int heap_size = (int) (ceil(1 / epsilon * epsilon));
  small_values.init(heap_size);

  for(i = 0l; i < arr_size; i++) {
    unsigned long hash_val = hash(arr[i]);
    if(small_values.size() < heap_size) {
      small_values.insert(hash_val);
    } else if(hash_val < small_values.peek()) {
      small_values.pop();
      small_values.insert(hash_val);
    }
  }
  long v = small_values.peek();
  return v;
}
