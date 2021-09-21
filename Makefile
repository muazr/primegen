CC=g++
CFLAGS=-std=c++11 -Wall -Wextra -Werror -O2 -I. 
DEPS = primenumbergenerator.h
OBJ = primenumbergenerator.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

prime-number-generator: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
