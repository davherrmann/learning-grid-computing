#include <stdio.h>
#include <pthread.h>

int cnt;
pthread_mutex_t mutex;
void nextcnt();

void* start_nextcnt(void* val) {
  nextcnt();
  return NULL;
}

void nextcnt() {
  printf("%d\n", cnt);
  pthread_mutex_lock(&mutex);
  if (cnt < 20) {
    cnt++;
    pthread_mutex_unlock(&mutex);

    pthread_t t;
    pthread_create(&t, NULL, &start_nextcnt, NULL);
    pthread_join(t, NULL);
    printf("joined\n");
  } else {
    pthread_mutex_unlock(&mutex);
    for (int i = 0; i < 1000; i++);
  }
}

int main(int argc, char const *argv[]) {
  cnt = 0;
  pthread_mutex_init(&mutex, NULL);
  nextcnt();

  return 0;
}
