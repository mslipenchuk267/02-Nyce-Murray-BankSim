#include "Account.h"

Account *Account_new(int id, int initialBalance) {
    Account *a = (Account *)malloc(sizeof(Account));
    a->id = id;
    a->balance = initialBalance;
    return a;
}

void Account_destroy(Account *a) {
    free(a);
}

void Account_deposit(Account *a, int amount) {
    int newBalance = a->balance + amount;
    a->balance = newBalance;
}

int Account_withdraw(Account *a, int amount) {
    if(amount <= a->balance) {
        int newBalance = a->balance - amount;
        a->balance = newBalance;
        return 1;
    } else {
        // This should never execute if task 4 is done right
        return 0;
    }
}
