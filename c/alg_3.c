#include <math.h>
#include <stdio.h>
#include "utils.h"
#include "rb.h"
/*
 * 
 */

void estimate_3 (
  unsigned long arr_size, 
  unsigned long *arr, 
  double epsilon, 
  hash_fn h, 
  hash_fn g, 
  struct rb_table **buffer, //buffer is an array of red-black trees
  unsigned int *t, //keeps track of how many leading zeroes we're on
  unsigned int *buf_elements) { //how many stuff with at least *t leading zeroes
  
  unsigned const int BUF_SIZE = ceil((576.0)/(epsilon * epsilon)); 
  unsigned long *temp = (unsigned long*) malloc(sizeof(unsigned long));
  for(unsigned long i = 0l; i < arr_size; i++) {
    
    unsigned int trail = trailing_zeroes(h.hash(arr[i]));
    *temp = g.hash(arr[i]);
    
    //if we have enough leading zeroes, add to buffer
    if (trail >= *t && !(rb_find(buffer[trail], temp))) { 
      (*buf_elements)++;
      
      unsigned long *new_long = (unsigned long*) malloc(sizeof(unsigned long));
      *new_long = g.hash(arr[i]);      
      rb_insert(buffer[trail], new_long);
      //if buffer is full, inc *t
      if(*buf_elements > BUF_SIZE) {
        (*buf_elements) -= ((buffer[*t])->rb_count);
        (*t)++; //never ever forget these parens
      }
    }
  }
  free(temp);
}
