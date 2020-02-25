#include "Bank.h"

#define NACCOUNTS 10
#define INITIAL_BALANCE 10000


/*---------------------Global Var Init-----------------------*/
// For accessing accountSet
pthread_mutex_t mutex_lock;
pthread_cond_t cond;
// For running test thread
pthread_mutex_t mutex_test_lock;
pthread_cond_t cond_test;
sem_t test_sem;
// for checking balance
pthread_mutex_t mutex_balance_lock;
// for signaling that first transaction_thread is done
pthread_mutex_t mutex_done_lock;
sem_t done_sem;
// Set holding account number of accounts currently
// making transactions
unordered_set<int> accountSet;

int main() {
    srand(time(NULL));
    // Declare/init condition variables, semaphore, and 
    //  unordered set for holding active accounts
    pthread_mutex_init(&mutex_lock, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex_balance_lock, NULL);
    pthread_mutex_init(&mutex_done_lock, NULL);
    unordered_set<int> accountSet;
    sem_init(&test_sem, 0, NTEST);
    sem_init(&done_sem, 0, 0); // set to false, when incremented first time we are done


    // Make bank and run our program. When Bank_open returns we are done
    Bank *b = Bank_new(NACCOUNTS, INITIAL_BALANCE);
    Bank_open(b);
    // Destroy our semaphore for the testing thread and bank to clean up
    sem_destroy(&test_sem);
    sem_destroy(&done_sem);
    Bank_destroy(b);
}