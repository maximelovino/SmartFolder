CC=gcc
FLAGS= -Wall -Wextra -std=c99 -c -g

all: TestHashSet TestStack TestList TestSearch

TestSearch: TestSearch.o Search.o List.o
	$(CC) $^ -o $@

TestSearch.o: TestSearch.c
	$(CC) $(FLAGS) $<

Search.o: Search.c Search.h
	$(CC) $(FLAGS) $<

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

TestList: TestList.o  List.o
	$(CC) $^ -o $@

TestList.o: TestList.c
		$(CC) $(FLAGS) $<

List.o: List.c List.h
	$(CC) $(FLAGS) $<

clean:
	rm *.o TestHashSet TestStack TestList TestSearch
