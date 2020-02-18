#include "Bank.h"

void *test_thread(void *vargp) {
  // Get Bank
  struct Bank *b = (struct Bank *)vargp;

  Bank_test(b);

  int i;
  for (i = 0; i < NTEST; ++i) {
    sem_post(&test_sem);
  }
}