#include "Bank.h"

void *test_thread(void *vargp) {
  // Get Bank
  struct Bank *b = (struct Bank *)vargp;

  // Wait for all transfer_threads to stop
  Bank_test(b);
  // Send signal for transfer_threads to begin again
  //free(b); // Free params now that we have what we need

}