#ifndef BANK_H
#define BANK_H
#include "common.h"
#include "Account.h"

#define NTEST 10

Bank *Bank_new(int numAccounts, int initialBalance);
void Bank_destroy(Bank *b);
void Bank_open(Bank *b);
void Bank_transfer(Bank *b, int from, int to, int amount);
void Bank_test(Bank *b);
int Bank_shouldTest(Bank *b);

TransferThreadParameters *TransferThreadParameters_new(Bank *b, int fromAccount, int maxAmount);
void *transfer_thread(void *vargp);
void *test_thread(void *vargp);
#endif