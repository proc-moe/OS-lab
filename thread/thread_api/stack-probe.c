#include "libs/thread.h"
#include <pthread.h>
#include <limits.h>

__thread char *base, *cur; // thread-local variables
__thread int id;

// objdump to see how thread-local variables are implemented
__attribute__((noinline)) void set_cur(void *ptr) { cur = ptr; }
__attribute__((noinline)) char *get_cur()         { return cur; }

void stackoverflow(int n) {
  set_cur(&n);
  if (n % 1024 == 0) {
    int sz = base - get_cur();
    printf("Stack size of T%d >= %d KB\n", id, sz / 1024);
  }
  stackoverflow(n + 1);
}

void Tprobe(int tid) {
  id = tid;
  base = (void *)&tid;
  stackoverflow(0);
}

int main() {
  pthread_attr_t tattr;
  int ret;
  ret = pthread_attr_init(&tattr);
  printf("pthread_attr_init ret=%d\n",ret);
  ret = pthread_attr_setstacksize(&tattr,1024*1024);
  printf("pthread_attr_setstacksize ret=%d\n",ret);
  setbuf(stdout, NULL);
  for (int i = 0; i < 4; i++) {
    create(Tprobe,&tattr);
  }
}
