    /* file minunit_example.c */

    #include <stdio.h>
    #include "minunit.h"
    #include <assert.h> 
    #include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
    #include <pthread.h> 

/*
Try using helgrind
https://valgrind.org/docs/manual/hg-manual.html
https://www.kdab.com/helgrind-howto/
http://cs.swan.ac.uk/~csoliver/ok-sat-library/internet_html/doc/doc/Valgrind/3.8.1/html/hg-manual.html

*/






    int tests_run = 0;

    int foo = 7;
    int bar = 4;

    static char * test_foo() {
        mu_assert("error, foo != 7", foo == 7);
        return 0;
    }

    static char * test_bar() {
        mu_assert("error, bar != 5", bar == 5);
        return 0;
    }

    static char * all_tests() {
        mu_run_test(test_foo);
        mu_run_test(test_bar);
        return 0;
    }

    int main(int argc, char **argv) {
        char *result = all_tests();
        
        pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
        int rc = pthread_mutex_init(&lock, NULL);
        assert(rc == 0); // always check success!


    /*
    To use a condition variable, one has to in addition have a lock that isassociated with this condition. 
    When calling either of the above routines,this lock should be held.
    The first routine,pthreadcondwait(), puts the calling thread tosleep, a
    nd thus waits for some other thread to signal it, 
    usuallywhensomething in the program has changed that the now-sleeping thread mightcare about. 
    A typical usage looks like this:
    
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t  cond = PTHREAD_COND_INITIALIZER;
    Pthread_mutex_lock(&lock);
    while (ready == 0)
        Pthread_cond_wait(&cond, &lock);
        
    Pthread_mutex_unlock(&lock);
    
    
    
    The code to wake a thread, which would run in some other thread,looks like this:
    Pthread_mutex_lock(&lock);
    ready = 1;
    Pthread_cond_signal(&cond);
    Pthread_mutex_unlock(&lock);
    */
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
         printf("ALL TESTS PASSED\n");
     }

     printf("Tests run: %d\n", tests_run);
     assert(tests_run == 1);
     return result != 0;
 }

