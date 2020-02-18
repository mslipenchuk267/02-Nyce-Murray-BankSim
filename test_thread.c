#include "Bank.h"

Bank *TransferTestThreadParameters_new(Bank *b) {
  Bank *bank = (Bank *)malloc(sizeof(Bank));

  return bank;
}

void *test_thread(void *vargp) {
  // Get Bank
  Bank *bank = (Bank *)vargp;
  Bank *b = bank;
  free(bank); // Free params now that we have what we need

  // Wait for all transfer_threads to stop
  //Bank_test(b);
  // Send signal for transfer_threads to begin again

}