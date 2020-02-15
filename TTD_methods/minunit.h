 /* file: minunit.h */

// #define NDEBUG

 #define mu_assert(message, test) do { if (!(test)) return message; } while (0)
 #define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)
 extern int tests_run;


/*
carry out test -- if fails return message

if there's message -- message got outputed
*/