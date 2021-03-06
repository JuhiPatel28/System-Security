#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <dlfcn.h>

void check(char* mem, int sz, int val) {
  for (int i = 0; i < sz; i++) {
    if (*(mem + i) != val) {
      printf("Failed at %i (%x)!\n", i, *(mem + i));
      break;
      }
  }
}

int main(int argc, char** argv) {
  
  void *handle = dlopen("/mnt/c/Users/Juhi/Desktop/a1/libmemsets.so", RTLD_LAZY);
  if(!handle) {printf("help handle \n");}
  void (*memset1)();
  void (*memset2)();
  void (*memset_asm)();
  void (*memset_sse)();
  memset1 = (void (*)())dlsym(handle, "memset1");
  memset2 = (void (*)())dlsym(handle, "memset2");
  memset_asm = (void (*)())dlsym(handle, "memset_asm");
  memset_sse = (void (*)())dlsym(handle, "memset_sse");


  unsigned int i, e = 1024, sz = 1024 * 1024;
  clock_t start, stop;
  char* mem = (char*) malloc(sz);

  start = clock();
  for (i = 0; i < e; i++) {
    memset(mem, 61, sz);
  }
  stop = clock();
  printf("Standard memset: %f\n", ((double) stop - start) / CLOCKS_PER_SEC);
  check(mem, sz, 61);

  memset(mem, 0, sz);

  start = clock();
  for (i = 0; i < e; i++) {
    // FIXME: memset1()
    (*memset1)(mem, 61, sz);
  }
  stop = clock();
  printf("Int memset1: %f\n", ((double) stop - start) / CLOCKS_PER_SEC);
  check(mem, sz, 61);
  memset(mem, 0, sz);


  start = clock();
  for (i = 0; i < e; i++) {
    // FIXME: memset2()
    (*memset2)(mem, 61, sz);
  }
  stop = clock();
  printf("Int memset2: %f\n", ((double) stop - start) / CLOCKS_PER_SEC);
  check(mem, sz, 61);
 

  memset(mem, 0, sz);
  
  start = clock();
  for (i = 0; i < e; i++) {
    // FIXME: memset_asm()
    (*memset_asm)(mem, 61, sz);
  }
  stop = clock();

  printf("ASM memset: %f\n", ((double) stop - start) / CLOCKS_PER_SEC);
  check(mem, sz, 61);

  memset(mem, 0, sz);
  
  start = clock();
  for (i = 0; i < e; i++) {
    // FIXME: memset_sse()
    (*memset_sse)(mem, 61, sz);
  }
  stop = clock();

  printf("SSE memset: %f\n", ((double) stop - start) / CLOCKS_PER_SEC);
  check(mem, sz, 61);
  return 0;
}