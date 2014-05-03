#include <stdlib.h>
#include "utils.h"

/*  First stage - use Flajolet-Martin algorithm to approximate F_0 within a constant factor
 *  Do this by hashing each input long and counting number of trailing 0s
 */
int hyper_log_log (int arr_size, long* arr, hash_fn hash) {
  int max_trailing_zeroes = 0;
  int i;

  for(i = 0; i < arr_size; i++) {
    long hash_value = hash.hash(arr[i]);
    max_trailing_zeroes = max(max_trailing_zeroes, trailing_zeroes(hash_value));
  }
  return max_trailing_zeroes; // F_0 is approximately 1 << max_trailing_zeroes with positive probability
}

/*
 * Actually, what we care about is the (bad) approximation from hyper-log-log -
 * We want a number (r) of approximately the same order of magnitude as F_0.
 */


int alg_2 (int arr_size, long* arr, long r, hash_fn hash) {
  
}

int main() {
}
