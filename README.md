# BankSim

## Matt Slipenchuk and Khai Nguyen

### Requirements:
Five tasks were required to be implemented as below:

* Task 1: Detect race condition and draw UML sequence diagram to explain where race condition happens.

* Task 2: Implement protection code to resolve the race condition issue. The protection code must allow the transferof funds between unrelated accounts. This was implemented by a mutex, a condition variable, and a set containing account IDs.

* Task 3. Refactor the test method of summing the balance in each account in a new and separate thread. Provide code protection so that the newly-created testing thread and any other amount transferring threads are running exclusively, i.e. the testing thread starts with a signal to all transferring threads, waits for all the transferring threads finishing the current transferring, and then takes over the testing task while all the transferring threads are waiting until the test is done. This was done by creating a new summing thread in Bank Transfer().

* Task 4. Implement a wait/notify solution to defer the transfer until the account balance becomes greater than the transferring amount (assume some the account will receive the fund later).

* Task 5. Implement a solution in which all thread stop fund transferring (bank is close) whenever one tread completes its fund transfers, since deadlock condition may occur (very rare) if one thread finishes all the fund transfers and exit. 


### Team work: 
How was the collaboration? What was done by each team member? Was one person more rapid than the other for the coding part? Who has done the writing, the tests? Did someone revise the work?  

* Matt Slipenchuk
1) Build/update Trello board
2) Assess where race condition happens for Task 1
3) Create/Update the UML sequence diagram for race condition
4) Design and revise code for Task2 implementation
5) Design and build semaphore implementation for summing thread in Task 3
6) Build implementation for deferring thread for Task 4
7) Build implementation for stopping fund transferring of all thread in Tasks 5
8) Create the second UML diagram for testing
9) Revised all Khai's work

* Khai Nguyen
1) Build/update Trello board
2) Assess where race condition happens for Task 1
3) Build the implemetation for code protection with mutual exclusion and condition variable for Task 2
4) Build, revise and test the counting semaphore implementation for summing thread in Task 3
5) Work with Matt to build and revise deferring transfer threads for Task 4
6) Proofread and test the implemetation for avoiding deadlock condition Task 5
7) Writeup project README.md
8) Revise all Matt's work


### Testing: 
Tests are automated using the Bank_shouldTest() and Bank_test() function. Apart from that we also found *minunit* and assert statements as decent automated test methods (included in TDD) but did not use them extensively compared to Bank_shouldTest() and Bank_test().  

Segmentation faults happened when implemeting condition variables, mainly because we forgot the initialization step using pthread_cond_init(). Both teammates write and execute the tests while we implement our methods and revising our teammates methods.

#### Race Condition Explanation
A race condition could occue because there are no locks or wait/signals around the Bank_transfer(...) function. When this function is called it makes 2 calls in the following order: 

1. Account_withdraw(from)
2. Account_deposit(to)

A thread can be superseded between function calls 1 and 2. 
If this happens then money is not deposited into the account and money exits the system.
As a result, the sum will not back up to the starting total. 

### UML Diagrams

#### Sequence Diagram - Race Condition in Bank_transfer(...)
![race condition uml](https://github.com/mslipenchuk267/02-Slipenchuk-Nguyen/blob/umlDev/Race%20Condition%20Sequence%20UML.jpg)

* Monitoring workflow: https://trello.com/b/5RbJQQHE/lab-5-bank-sim

#### Sequence Diagram - Calling Bank_test(b) After Task 3 solution
![bank test uml](https://github.com/mslipenchuk267/02-Slipenchuk-Nguyen/blob/umlDev/Test%20Solution%20After%20Task%203%20Lab%205.png)
