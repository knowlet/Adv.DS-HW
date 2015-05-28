CC=gcc
OBJS=LeftistTree.o
main: main.o LeftistTree.o LeftistTreeW.o
	$(CC) main.o LeftistTree.o LeftistTreeW.o -o leftistTree
main.o: main.c
	$(CC) -c main.c -o main.o
LeftistTree.o:
	$(CC) -c LeftistTree.c LeftistTreeW.c
clean:
	rm *.o leftistTree