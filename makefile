CC=gcc

BankSim: *.c
	g++ -pthread -o BankSim *.c
