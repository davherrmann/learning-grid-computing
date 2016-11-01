// use POSIX standard 2004
#define _XOPEN_SOURCE 700

#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

static const int CHAR_BUFFER_SIZE = 1024;
static const int MASTER_ID = 0;
static const int RESULT_HOSTNAME = 0;

void master(const int size) {
  char buffer[CHAR_BUFFER_SIZE];

  for (int n = 0; n < size; n++) {
    MPI_Recv(buffer, CHAR_BUFFER_SIZE, MPI_CHAR, MPI_ANY_SOURCE, RESULT_HOSTNAME, MPI_COMM_WORLD, NULL);
    printf("%s\n", buffer);
  }
}

void slave() {
  char buffer[CHAR_BUFFER_SIZE];
  gethostname(buffer, CHAR_BUFFER_SIZE);

  MPI_Send(buffer, CHAR_BUFFER_SIZE, MPI_CHAR, MASTER_ID, RESULT_HOSTNAME, MPI_COMM_WORLD);
}

int main(int argc, char *argv[]) {
  int size, rank;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == MASTER_ID) {
    master(size);
  } else {
    slave();
  }

  MPI_Finalize();
  return 0;
}
