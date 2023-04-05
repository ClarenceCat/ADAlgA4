# File: Makefile
# Name: Daniel Grew - 0978547
# Description: This is the make file which compiles all components of the assignment 

# macros 
INC = inc/
SRC = src/
BIN = bin/

CC = gcc 
CFLAGS = -Wall -std=c11 -g


all: $(BIN)assignment4

$(BIN)assignment4: $(BIN)main.o $(BIN)P11.o $(BIN)P12.o $(BIN)P2.o $(BIN)filehandler.o $(BIN)tree.o
	$(CC) $(CFLAGS) -L$(BIN) $(BIN)*.o -o $(BIN)assignment4 -lm

$(BIN)main.o: $(SRC)main.c $(INC)assignment4.h
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)main.c -o $(BIN)main.o 

$(BIN)P11.o: $(SRC)P11.c 
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)P11.c -o $(BIN)P11.o 

$(BIN)P12.o: $(SRC)P12.c 
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)P12.c -o $(BIN)P12.o 

$(BIN)P2.o: $(SRC)P2.c 
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)P2.c -o $(BIN)P2.o 

$(BIN)filehandler.o: $(SRC)filehandler.c $(INC)assignment4.h
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)filehandler.c -o $(BIN)filehandler.o 

$(BIN)tree.o: $(SRC)tree.c $(INC)assignment4.h
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)tree.c -o $(BIN)tree.o 


clean: 
	rm $(BIN)*.o $(BIN)assignment4