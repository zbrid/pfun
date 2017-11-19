#include <stdio.h>       /* standard I/O routines                 */
#include <pthread.h>     /* pthread functions and data structures */
#include <unistd.h>
void* PrintHello(void* data)
{
    pthread_t tid = (pthread_t)data;    /* data received by thread */

    pthread_join(tid, NULL);            /* wait for thread tid     */
    printf("HELLO - NEW THREAD!!! %u - got %u\n", pthread_self(), data);
    pthread_exit(NULL);	                /* terminate the thread    */
}

/* like any C program, program's execution begins in main */
int main(int argc, char* argv[])
{
    int        rc;         	       /* return value                  */
    pthread_t  thread_id;     	       /* thread's ID (just an integer) */
    // there is a typo on the example: this was originally an int and
    // that caused some problem that made the program function in
    // an unexpected way (the new thread completed before the main thread)
    // with this changed to type pthread_t, the main thread completes (since
    // the new thread called pthread-join on it in its start routine)
    // and then the new thread completes, then the program exits
    // typo from this site: http://www.csc.villanova.edu/~mdamian/threads/posixthreads.html
    pthread_t        tid;

    tid = pthread_self();

    rc = pthread_create(&thread_id, NULL, PrintHello, (void*)tid);  
    if(rc)                             /* could not create thread */
    {
        printf("\nERROR: return code from pthread_create is %d \n", rc);
        exit(1);
    }
    sleep(1);
    printf("\n Created new thread (%u) from ME=(%u)... \n", thread_id, tid);
    pthread_exit(NULL);		
}
