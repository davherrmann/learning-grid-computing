#include <stdio.h>
#include <pthread.h>

float integrate(float a, float b);

struct Workload {
  float a;
  float b;
  float result;
};

void* start_integrate(void* val) {
  struct Workload *workload = val;
  workload->result = integrate(workload->a, workload->b);

  printf("p result: %f\n", workload->result);

  return NULL;
}

float f(float x) { return x * x + 1; }
float df(float x) { return 2 * x; }

float integrate(float a, float b) {
  float m = (a + b) / 2;

  // TODO user input?
  float epsilon_1 = 0.01;
  float epsilon_2 = 0.0625;

  if (df(m) / f(m) > epsilon_1 && b - a > epsilon_2) {
    struct Workload workload = {m, b};
    pthread_t thread;

    pthread_create(&thread, NULL, start_integrate, &workload);
    float i_0 = integrate(a, m);

    printf("o result: %f\n", i_0);

    pthread_join(thread, NULL);

    return i_0 + workload.result;
  } else {
    return (b - a) * f(m);
  }
}

int main(int argc, char const *argv[]) {
  float i = integrate(0, 1);
  printf("%f\n", i);
  return 0;
}
