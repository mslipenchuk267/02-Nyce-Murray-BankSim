#include "Bank.h"

#define NACCOUNTS 10
#define INITIAL_BALANCE 10000

int main() {
    srand(time(NULL));

    Bank *b = Bank_new(NACCOUNTS, INITIAL_BALANCE);
    Bank_open(b);
    Bank_destroy(b);
}