#include <stdlib.h>

typedef struct heap {
  int capacity; 
  unsigned long *heap;
  int heap_size;

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

  int size() {
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
    if(heap_size == capacity) return;

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
    int index = 0;

    while(2 * index + 1 < heap_size) {
      int left_child = 2 * index + 1;
      int right_child = 2 * index + 2;

      if(left_child < heap_size && right_child < heap_size) { // if both children are in the heap,
        
        if(heap[left_child] > heap[index] && heap[left_child] > heap[right_child]) { // if the left child is the largest, raise it up
          swap(&(heap[left_child]), &(heap[index]));
        } else if (heap[right_child] > heap[index]) { //otherwise raise the right child up
          swap(&(heap[right_child]), &(heap[index]));
        }
      } else if (left_child < heap_size) { //if there's only the left child (heap invariant says there's only a left child if there's a right child)
        if(heap[left_child] > heap[index]) {
          swap(&(heap[left_child]), &(heap[index]));
        }
      } else {}

    }
    return return_value;
  }

} heap;

