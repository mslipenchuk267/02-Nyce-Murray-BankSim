#include "Bank.h"

#define NACCOUNTS 10
#define INITIAL_BALANCE 10000

pthread_mutex_t mutex_lock;
pthread_cond_t cond;
unordered_set<int> accountSet;

int main() {
    srand(time(NULL));
    // initialize
    pthread_mutex_init(&mutex_lock, NULL);
    pthread_cond_init(&cond, NULL);
    unordered_set<int> accountSet;

    Bank *b = Bank_new(NACCOUNTS, INITIAL_BALANCE);
    Bank_open(b);
    Bank_destroy(b);
}