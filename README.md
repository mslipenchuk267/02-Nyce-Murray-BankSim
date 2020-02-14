# BankSim

## Race Condition Explanation
A race condition could occue because there are no locks or wait/signals around the Bank_transfer(...) function. When this function is called it makes 2 calls in the following order: 

1. Account_withdraw(from)
2. Account_deposit(to)

A thread can be superseded between function calls 1 and 2. 
If this happens then money is not deposited into the account and money exits the system.
As a result, the sum will not back up to the starting total. 


## Race Condition in Bank_transfer(...)
![race condition uml](https://github.com/mslipenchuk267/02-Slipenchuk-Nguyen/blob/umlDev/Race%20Condition%20Sequence%20UML.jpg)

* Monitoring workflow: https://trello.com/b/5RbJQQHE/lab-5-bank-sim
