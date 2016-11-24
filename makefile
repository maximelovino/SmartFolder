CC=gcc
FLAGS= -Wall -Wextra -std=c99 -c -g

TestHashSet: TestHashSet.o HashSet.o
	$(CC) $^ -o $@

TestHashSet.o: TestHashSet.c
	$(CC) $(FLAGS) $<

HashSet.o: HashSet.c HashSet.h
	$(CC) $(FLAGS) $<

clean:
	rm *.o TestHashSet
