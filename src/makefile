CC=gcc
FLAGS= -Wall -Wextra -std=gnu99 -c -g
DS=HashSet.o List.o Stack.o
BD=Logger.o Syscall.o Search.o
LINKFLAGS= -lrt

all: TestHashSet TestStack TestList TestSearch TestParser TestLogger SmartFolder TestLinker

SmartFolder: SmartFolder.o $(DS) $(BD) Parser.o
	$(CC) $^ -o $@ $(LINKFLAGS)

SmartFolder.o: SmartFolder.c
	$(CC) $(FLAGS) $<

Syscall.o: Syscall.c Syscall.h
	$(CC) $(FLAGS) $<

TestParser: TestParser.o $(DS) $(BD) Parser.o
	$(CC) $^ -o $@ $(LINKFLAGS)

Parser.o: Parser.c Parser.h
	$(CC) $(FLAGS) $<

TestLogger: TestLogger.o Logger.o
	$(CC) $^ -o $@ $(LINKFLAGS)

Logger.o: Logger.c Logger.h
	$(CC) $(FLAGS) $<

TestLogger.o: TestLogger.c
	$(CC) $(FLAGS) $<

TestSearch: TestSearch.o Search.o List.o
	$(CC) $^ -o $@ $(LINKFLAGS)

TestSearch.o: TestSearch.c
	$(CC) $(FLAGS) $<

Search.o: Search.c Search.h
	$(CC) $(FLAGS) $<

TestLinker: TestLinker.o Linker.o Syscall.o Logger.o
	$(CC) $^ -o $@ $(LINKFLAGS)

TestLinker.o: TestLinker.c
	$(CC) $(FLAGS) $<

Linker.o: Linker.c Linker.h
	$(CC) $(FLAGS) $<

TestHashSet: TestHashSet.o Logger.o HashSet.o
	$(CC) $^ -o $@ $(LINKFLAGS)

TestHashSet.o: TestHashSet.c
	$(CC) $(FLAGS) $<

HashSet.o: HashSet.c HashSet.h
	$(CC) $(FLAGS) $<

TestStack: TestStack.o  Stack.o
	$(CC) $^ -o $@ $(LINKFLAGS)

TestStack.o: TestStack.c
		$(CC) $(FLAGS) $<

Stack.o: Stack.c Stack.h
	$(CC) $(FLAGS) $<

TestList: TestList.o  List.o
	$(CC) $^ -o $@ $(LINKFLAGS)

TestList.o: TestList.c
		$(CC) $(FLAGS) $<

List.o: List.c List.h
	$(CC) $(FLAGS) $<

clean:
	rm *.o TestHashSet TestStack TestList TestSearch TestParser SmartFolder TestLogger TestLinker
