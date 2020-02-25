#ifndef COMMON_H
#define COMMON_H
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <iostream>
#include <fstream> // file opss
#include <set> // for set operations 
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // for size_t
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>
#include <unordered_set>

using namespace std;

// declare mutexes & condition variables
extern pthread_mutex_t mutex_lock;
extern pthread_mutex_t mutex_balance_lock;
extern pthread_mutex_t mutex_done_lock;
extern pthread_cond_t cond;
extern sem_t done_sem;
extern sem_t test_sem;
extern unordered_set<int> accountSet;

typedef struct Account {
    int balance;
    int id;
    pthread_t thread;
    pthread_cond_t cond_balance;
} Account;

typedef struct Bank {
    int initialBalance;
    int numAccounts;
    long ntransacts;
    int ntransactsInProgress;
    Account **accounts;
} Bank;

typedef struct TransferThreadParameters {
    Bank *b;
    int fromAccount;
    int maxAmount;
} TransferThreadParameters;

#endif