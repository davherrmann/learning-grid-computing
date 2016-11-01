#include <stdio.h>
#include <stdlib.h>

// flag:
// - 0: don't add a 1 per int array entry
// - 1: add 1 per int array entry
int work(int start, int stop, int flag, int *arrayptr) {
  int partial=0;
  if(flag==0)
    for(;start<stop;start++) partial += *arrayptr++;
  else
    for(;start<stop;start++) partial += 1+*arrayptr++;
  return partial;
}

int main(int argc, char *argv[]) {
  int *aptr;
  int i;
  int result1, result2, result3, result4;
  aptr = (int*)malloc(1000*sizeof(int));
  for(i=0;i<1000;i++) *(aptr+i) = i;
  result1 = work(0, 500, 0, aptr);
  result2 = work(0, 500, 1, aptr);
  result3 = work(500, 1000, 0, aptr);
  result4 = work(500, 1000, 1, aptr);
  if((result1+result3) == (result2+result4-1000))
    printf("Correct Result!\n");
  else
    printf("Wrong Result!\n");
  return 0;
}
