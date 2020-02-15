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
        
        /*------------------mutex & cond var implement---------------*/
        pthread_mutex_lock(&mutex_lock);
        while (accountSet.count(toAccount) != 0 && accountSet.count(fromAccount) != 0){
            pthread_cond_wait(&cond, &mutex_lock);
        }

        accountSet.insert(toAccount);
        accountSet.insert(fromAccount);
        /*------------------Bank transfer----------------*/
        Bank_transfer(b, fromAccount, toAccount, amount);
        /*-----------------------------------------------*/
        accountSet.erase(toAccount);
        accountSet.erase(fromAccount);

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex_lock);
    }

    printf("Account[%d] is done.\n", fromAccount);
}
