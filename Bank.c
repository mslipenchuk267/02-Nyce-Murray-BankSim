#include "Bank.h"

Bank *Bank_new(int numAccounts, int initialBalance) {
    Bank *b = (Bank *)malloc(sizeof(Bank));
    b->initialBalance = initialBalance;
    b->numAccounts = numAccounts;
    b->ntransacts = 0;
    b->accounts = (Account **)malloc(numAccounts * sizeof(Account *));
    for(int i = 0; i < numAccounts; ++i) {
        b->accounts[i] = Account_new(i, initialBalance);
        pthread_cond_init(&b->accounts[i]->cond_balance, NULL);
        printf("Account\t[%d]\tcreated\t& CV made as well\n", i);

    }
    
    return b;
}

void Bank_destroy(Bank *b) {
    for(int i = 0; i < b->numAccounts; ++i) {
        Account_destroy(b->accounts[i]);
    }
    free(b);
}

void Bank_open(Bank *b) {
    for(int i = 0; i < b->numAccounts; ++i) {
        TransferThreadParameters *params = TransferThreadParameters_new(b, i, b->initialBalance);
        pthread_create(&b->accounts[i]->thread, NULL, transfer_thread, params);
    }

    for(int i = 0; i < b->numAccounts; ++i) {
        pthread_join(b->accounts[i]->thread, NULL);
    }

    Bank_test(b);

    puts("Bank is finished running.");
}

void Bank_transfer(Bank *b, int from, int to, int amount) {
    // Uncomment line when race condition in Bank_test() has been resolved.
    if(Bank_shouldTest(b)) {
      // Create testing thread
      pthread_t testing_thread;
      // Execute test_thread
      pthread_create(&testing_thread, NULL, test_thread, (void *) b);
      // Join test thread after done executing Bank_test()
      pthread_join(testing_thread, NULL);
    }

    if(Account_withdraw(b->accounts[from], amount)) {
        Account_deposit(b->accounts[to], amount);
    }
}

/* test [agregate amount from all account] & [total initialBalance] */
void Bank_test(Bank *b) {
    int sum = 0;

    for(int i = 0; i < b->numAccounts; ++i) {
        pthread_t currentThreadId = pthread_self();
        Account *currAccount = b->accounts[i];
        printf("%lu Account[%d] balance %d\n", pthread_self(), currAccount->id, currAccount->balance);
        sum += b->accounts[i]->balance;
    }
    printf("%lu Sum: %d\n", pthread_self(), sum);
    if(sum != b->numAccounts * b->initialBalance) {
        printf("%lu Money was gained or lost!\n", pthread_self());
        exit(0);
    } else {
        printf("%lu The bank is in balance!\n", pthread_self());
    }
}

/* should test every 10 transacs */
int Bank_shouldTest(Bank *b) {
    b->ntransacts++;
    return b->ntransacts % NTEST == 0;
}