#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
 
// A normal C function that is executed as a thread 
// when its name is specified in pthread_create()
void *myThreadFun(void *vargp)
{
    sleep(1);
    printf("Printing GeeksQuiz from Thread \n");
    printf("%d printing a calculation\n", 1 + 1);
    return NULL;
}
  
int main()
{
    pthread_t tid;
    printf("Before Thread\n");
    // 1: pthread pointer
    // 2: idk
    // 3: The function the to-be-created thread will execute
    // 4: To pass args to the thread
    pthread_create(&tid, NULL, myThreadFun, NULL);
    // function for threads
    // equivalent to ewiat for processes
    // blocks the calling thread until the thread with identifier
    //    equal to the first arg terminates -- I don't understand why
    //    you would create a thread and execute it in a way that blocks
    //    the calling thread. doesn't that defeat the purpose of creating
    //    a new thread? I thought the point was to start a new thread
    //    while continuing to execute code in the calling thread?
    pthread_join(tid, NULL);
    printf("After Thread\n");
    exit(0);
}
