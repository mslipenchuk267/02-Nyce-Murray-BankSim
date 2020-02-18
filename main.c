#include "Bank.h"

#define NACCOUNTS 10
#define INITIAL_BALANCE 10000

// For accessing accountSet
pthread_mutex_t mutex_lock;
pthread_cond_t cond;
// For running test thread
pthread_mutex_t mutex_test_lock;
pthread_cond_t cond_test;
sem_t test_sem;
// Set holding account number of accounts currently
// making transactions
unordered_set<int> accountSet;

int main() {
    srand(time(NULL));
    // initialize
    pthread_mutex_init(&mutex_lock, NULL);
    pthread_cond_init(&cond, NULL);
    unordered_set<int> accountSet;
    sem_init(&test_sem, 0, NTEST);

    Bank *b = Bank_new(NACCOUNTS, INITIAL_BALANCE);
    Bank_open(b);
    Bank_destroy(b);
}