#include <stdio.h>
#include <pthread.h>

int cnt;
void nextcnt();

void* start_nextcnt(void* val) {
  nextcnt();
  return NULL;
}

void nextcnt() {
  printf("%d\n", cnt);
  if (cnt < 20) {
    // TODO mutex lock
    cnt++;

    pthread_t t;
    pthread_create(&t, NULL, &start_nextcnt, NULL);
    pthread_join(t, NULL);
    printf("joined\n");
  } else {
    for (int i = 0; i < 1000; i++);
  }
}

int main(int argc, char const *argv[]) {
  cnt = 0;
  nextcnt();

  return 0;
}
