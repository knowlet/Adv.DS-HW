CC=gcc
OBJS=LeftistTree.o
main: main.o LeftistTree.o
	$(CC) main.o LeftistTree.o -o leftistTree
main.o: main.c
	$(CC) -c main.c -o main.o
LeftistTree.o:
	$(CC) -c LeftistTree.c -o LeftistTree.o
clean:
	rm *.o leftistTree