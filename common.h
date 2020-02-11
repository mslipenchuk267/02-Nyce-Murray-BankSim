#ifndef COMMON_H
#define COMMON_H
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Account {
    int balance;
    int id;
    pthread_t thread;
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