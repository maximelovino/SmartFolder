CC=gcc
FLAGS= -Wall -Wextra -std=gnu99 -c -g
DS=HashSet.o List.o Stack.o
BD=Logger.o Syscall.o Search.o Linker.o SysFile.o Daemon.o Parser.o
LINKFLAGS= -lrt

all: TestHashSet TestStack TestList TestSearch TestParser TestLogger SmartFolder TestLinker

SmartFolder: SmartFolder.o $(DS) $(BD)
	$(CC) $^ -o $@ $(LINKFLAGS)

%.o: %.c
	$(CC) $(FLAGS) $<

TestParser: TestParser.o $(DS) $(BD) Parser.o
	$(CC) $^ -o $@ $(LINKFLAGS)

TestLogger: TestLogger.o Logger.o
	$(CC) $^ -o $@ $(LINKFLAGS)

TestSearch: TestSearch.o Search.o List.o Logger.o Syscall.o
	$(CC) $^ -o $@ $(LINKFLAGS)

TestLinker: TestLinker.o Linker.o Syscall.o Logger.o
	$(CC) $^ -o $@ $(LINKFLAGS)

TestHashSet: TestHashSet.o Logger.o HashSet.o
	$(CC) $^ -o $@ $(LINKFLAGS)

TestStack: TestStack.o  Stack.o Logger.o
	$(CC) $^ -o $@ $(LINKFLAGS)

TestList: TestList.o  List.o Logger.o
	$(CC) $^ -o $@ $(LINKFLAGS)

clean:
	rm *.o TestHashSet TestStack TestList TestSearch TestParser SmartFolder TestLogger TestLinker
