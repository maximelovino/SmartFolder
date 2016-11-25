CC=gcc
FLAGS= -Wall -Wextra -std=c99 -c -g

all: TestHashSet TestStack

TestHashSet: TestHashSet.o HashSet.o
	$(CC) $^ -o $@

TestHashSet.o: TestHashSet.c
	$(CC) $(FLAGS) $<

HashSet.o: HashSet.c HashSet.h
	$(CC) $(FLAGS) $<

TestStack: TestStack.o  Stack.o
	$(CC) $^ -o $@

TestStack.o: TestStack.c
		$(CC) $(FLAGS) $<

Stack.o: Stack.c Stack.h
	$(CC) $(FLAGS) $<

clean:
	rm *.o TestHashSet
