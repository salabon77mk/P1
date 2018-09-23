CC=gcc
CFLAGS=-Wall -Wextra
DEPS = procexplore.h statexplore.h cmdparse.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

makemain: main.o statexplore.o procexplore.o cmdparse.o
	$(CC) -o main main.o statexplore.o procexplore.o cmdparse.o
 

