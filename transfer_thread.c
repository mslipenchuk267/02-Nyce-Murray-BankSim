#include "Bank.h"
TransferThreadParameters *TransferThreadParameters_new(Bank *b, int fromAccount, int maxAmount) {
    TransferThreadParameters *param = (TransferThreadParameters *)malloc(sizeof(TransferThreadParameters));
    param->b = b;
    param->fromAccount = fromAccount;
    param->maxAmount = maxAmount;

    return param;
}

void *transfer_thread(void *vargp) {
    TransferThreadParameters *param = (TransferThreadParameters *)vargp;
    Bank *b = param->b;
    int fromAccount = param->fromAccount;
    int maxAmount = param->maxAmount;
    free(param);
    
    for(int i = 0; i < 10000; ++i) {
        int toAccount = (int)(rand() % b->numAccounts);
        int amount = (int)(rand() % maxAmount);


        pthread_mutex_lock(&mutex_balance_lock);
        while (b->accounts[fromAccount]->balance < amount){
            printf("Account [%d] Deffered (balance < amount) | $%d < $%d\n", fromAccount, b->accounts[fromAccount]->balance, amount);
            pthread_cond_wait(&b->accounts[fromAccount]->cond_balance, &mutex_balance_lock);
        }
        pthread_mutex_unlock(&mutex_balance_lock);

        /*-----------------Do a semaphore wait for test--------------*/
        // Can go through here NTEST times
        // When NTEST bank transfers are executed, we make test_thread
        // and test_thread increments test_sem back to 10 so we can resume.
        sem_wait(&test_sem);
        //printf("Transfer: Account Number, balance [%d,\t$%d]\tsending\t$%d\t-> Account [%d]\n", fromAccount, b->accounts[fromAccount]->balance, amount, toAccount);
        /*------------------mutex & cond var implement---------------*/
        pthread_mutex_lock(&mutex_lock);
        while (accountSet.count(toAccount) != 0 && accountSet.count(fromAccount) != 0){
            pthread_cond_wait(&cond, &mutex_lock);
        }

        accountSet.insert(toAccount);
        accountSet.insert(fromAccount);
        /*------------------Bank transfer----------------*/
        printf("Account [%d, %d]\t sending $%d\t-> Account [%d]\n", fromAccount, b->accounts[fromAccount]->balance, amount, toAccount);
        Bank_transfer(b, fromAccount, toAccount, amount);
        /*-----------------------------------------------*/
        accountSet.erase(toAccount);
        accountSet.erase(fromAccount);

        pthread_cond_signal(&cond); // &cond is pthread_cond_t*
        pthread_cond_signal(&b->accounts[toAccount]->cond_balance); // &cond is pthread_cond_t*
        pthread_mutex_unlock(&mutex_lock);
    }

    printf("Account[%d] is done.\n", fromAccount);
}
