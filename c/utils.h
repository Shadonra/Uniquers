#include <stdlib.h>
#include <time.h>
#include "rb.h"
#define UTILS_H 1

unsigned long min(unsigned long a, unsigned long b);
unsigned long max(unsigned long a, unsigned long b);

int trailing_zeroes(long l);
int compare_long (const void*, const void*, void*);
/* An implementation of a hash with (implicit) striped matrix. 
   This hash is 2-wise independent (2-universal)
*/
typedef struct hash_fn {
  long stripe[2];
  long offset;
  
  void init() {
    srand(time(NULL));
    
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
    return ret;
  }
} hash_fn;

/*
 * Array implementation of a heap 
 */
typedef struct heap {
  unsigned int capacity; 
  unsigned long *heap;
  unsigned int heap_size;

  void init(int c) {
    capacity = c;
    heap_size = 0;
    heap = (unsigned long*) calloc(sizeof(long), c);
  }
  
  void swap (unsigned long* a, unsigned long* b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
  }

  unsigned int size() {
    return heap_size;
  }

  void bubble(int index) {
    int parent = (index - 1)/2;
    if(heap[parent] < heap[index]) {
      swap(&(heap[parent]), &(heap[index]));
      bubble(parent);
    }
  }

  void insert(unsigned long l) {
    if(heap_size == capacity) {
        return;
    } 
    
    heap[heap_size] = l;
    bubble(heap_size);
    heap_size += 1;
  }
  
  unsigned long peek() {
    return heap[0];
  }
  
  unsigned long pop() {
    unsigned long return_value = heap[0];
    
    heap[0] = heap[heap_size - 1]; //replace root with the last heap node
    unsigned int index = 0;

    while(2 * index + 1 < heap_size) {
      unsigned int left_child = 2 * index + 1;
      unsigned int right_child = 2 * index + 2;

      if(left_child < heap_size && right_child < heap_size) { // if both children are in the heap,
        
        if(heap[left_child] > heap[index] && heap[left_child] > heap[right_child]) { // if the left child is the largest, raise it up
          swap(&(heap[left_child]), &(heap[index]));
          index = left_child;
        } else if (heap[right_child] > heap[index]) { //otherwise raise the right child up
          swap(&(heap[right_child]), &(heap[index]));
          index = right_child;
        } else { break; } // otherwise done
      } else if (left_child < heap_size) { //if there's only the left child (heap invariant says there's only a left child if there's a right child)
        if(heap[left_child] > heap[index]) {
          swap(&(heap[left_child]), &(heap[index]));
          index = left_child;
        } else { break; }
      } else { break; }

    }
    heap_size--;
    return return_value;
  }

} heap;

