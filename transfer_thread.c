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

        /*---mutex & cond var for accounts with not enough balance---*/
        pthread_mutex_lock(&mutex_balance_lock);
        while (b->accounts[fromAccount]->balance < amount){ // 
            // Now we continue to wait until balance is greater or equal
            // to amount i.e. we can do transaction
            pthread_cond_wait(b->accounts[fromAccount]->cond_balance, &mutex_balance_lock);
        }
        // Can unlock because we are done checking current balance of the
        // account
        pthread_mutex_unlock(&mutex_balance_lock);


        /*-----------------Do a semaphore wait for test--------------*/
        // Can go through here NTEST times
        // When NTEST bank transfers are executed, we make test_thread
        // and test_thread increments test_sem back to 10 so we can resume.
        sem_wait(&test_sem);

        /*----mutex & cond var for currently transacting accounts----*/
        pthread_mutex_lock(&mutex_lock);
        while (accountSet.count(toAccount) != 0 && accountSet.count(fromAccount) != 0){
            pthread_cond_wait(&cond, &mutex_lock);
        }
        // Add accounts currently transacting to accountSet
        // accountSet is an unordered list of all acounts that 
        //  are involvlsed in a bank transfer.
        accountSet.insert(toAccount);
        accountSet.insert(fromAccount);
        /*------------------Bank transfer----------------*/
        Bank_transfer(b, fromAccount, toAccount, amount);
        /*-----------------------------------------------*/
        // Now that the transaction is done, we can remove the
        //  acounts from the set of active accounts.
        accountSet.erase(toAccount);
        accountSet.erase(fromAccount);

        pthread_cond_signal(&cond);
        // can signal wait for potentially deffered accounts
        //  because they got money added into their account
        pthread_cond_signal(b->accounts[toAccount]->cond_balance);
        pthread_mutex_unlock(&mutex_lock);
    }

    printf("Account[%d] is done.\n", fromAccount);
}
