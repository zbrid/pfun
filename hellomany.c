#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREADS 50
// I wrote this mostly without help. I added the MAX_THREAD thing after
// looking at the solution and also adding checking the return code
// after looking at the solution. Otherwise I wrote it.
void* PrintHello(void* data) {
  int my_data = (int) data;

  pthread_detach(pthread_self());
  printf("Hello from NEW thread (%u) - I was created in iteration %d.\n", pthread_self(), data);
  pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
  int i, n, rc;
  pthread_t curr_tid = pthread_self();

  if (argc == 1) {
    printf("Please pass a number.");
    exit(0);
  }
  n = atoi(argv[1]);
 
  if (n > MAX_THREADS) n = MAX_THREADS;

  for(i = 1; i <= n; i++) {
    pthread_t tid;
    pthread_create(&tid, NULL, PrintHello, (void*) i);
    if (rc) {
      printf("ERROR: return code from pthread_create is %d\n", rc);
      exit(1);
    }
    printf("I am thread %u. Created new thread (%u) in iteration %d...\n", curr_tid, tid, i);

    if (i % 5 == 0) {
      sleep(1);
    }
  }
  pthread_exit(NULL);
}
  
