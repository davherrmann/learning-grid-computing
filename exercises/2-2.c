#include <stdio.h>
#include <pthread.h>

float integrate(float a, float b);

struct Workload {
  float a;
  float b;
  float result;
};

float epsilon_1 = 0.01;
float epsilon_2 = 0.0625;

void* start_integrate(void* val) {
  struct Workload *workload = val;
  workload->result = integrate(workload->a, workload->b);

  return NULL;
}

float f(float x) { return x * x + 1; }
float df(float x) { return 2 * x; }

float integrate(float a, float b) {
  float m = (a + b) / 2;

  if (df(m) / f(m) > epsilon_1 && b - a > epsilon_2) {
    struct Workload workload = {m, b};
    pthread_t thread;

    pthread_create(&thread, NULL, start_integrate, &workload);
    float i_0 = integrate(a, m);

    pthread_join(thread, NULL);

    return i_0 + workload.result;
  } else {
    return (b - a) * f(m);
  }
}

int main(int argc, char const *argv[]) {
  float a, b;

  // TODO don't use scanf (no bound checking)
  printf("epsilon_1: ");
  scanf("%f", &epsilon_1);

  printf("epsilon_2: ");
  scanf("%f", &epsilon_2);

  printf("a: ");
  scanf("%f", &a);

  printf("b: ");
  scanf("%f", &b);

  float i = integrate(a, b);
  printf("f(x) = x^2 + 1; integrate(a, b) = %f\n", i);
  return 0;
}
