#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define BUF_SIZE 1024

int main(int argc, char* argv[]) {
  if(argc != 4) {
    printf("Usage: <#elements> <max-element> <outfile>");
  }
  
  int elements = atoi(argv[1]);
  int max_element = atoi(argv[2]);
  FILE* outfile = fopen(argv[3], "w");
  long* buf = (long*) malloc(sizeof(long) * BUF_SIZE);
  
  for(int i = 0; i * BUF_SIZE < elements; i++) {
    for(int j = 0; j < BUF_SIZE; j++) {
      int l, r;
      l = rand();
      r = rand();
      buf[j] = (((long) l) << 32 | (long) r) % max_element;
    }
    fwrite((void*) buf, BUF_SIZE, sizeof(long), outfile);
  }
  fclose(outfile);
}
