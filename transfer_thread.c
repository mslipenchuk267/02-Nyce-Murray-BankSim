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

        // Check if done before proceeding to checking if we can actually afford transaction
        pthread_mutex_lock(&mutex_done_lock);
        int done_sem_value;
        sem_getvalue(&done_sem, &done_sem_value);
        //printf("Not done thread | done sem value %d\n", done_sem_value);
        if(done_sem_value > 0) { // Indicating 1 thread just finished
            printf("Thread [%d] Done : done_sem value = %d\n", fromAccount, done_sem_value);
            pthread_mutex_unlock(&mutex_done_lock);
            //pthread_exit((void *)pthread_self());
            //pthread_cancel(pthread_self());
            return NULL;
            //break;
        }
        pthread_mutex_unlock(&mutex_done_lock);


        pthread_mutex_lock(&mutex_balance_lock);
        // Check if balance is less than amount to transefer 
        while (b->accounts[fromAccount]->balance < amount){
            // Defer the transaction
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

    // Signal all threads that it's time to return and join
    pthread_mutex_lock(&mutex_done_lock);
    sem_post(&done_sem); 
    pthread_mutex_unlock(&mutex_done_lock);
    int done_sem_value;
    sem_getvalue(&done_sem, &done_sem_value);
    printf("-------------------------------\n\n\n\n********\nFirst done Thread\n********\n Thread [%d] : done_sem value = %d\n\n\n\n-------------------------------\n", fromAccount, done_sem_value);
    //pthread_exit((void *)pthread_self());
    return NULL;
    //pthread_cancel(pthread_self());
}
