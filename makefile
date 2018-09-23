CC=gcc
CFLAGS=-Wall -Wextra
DEPS = procexplore.h statexplore.h cmdparse.h
OBJ = main.o statexplore.o procexplore.o cmdparse.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cs537: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
 
.PHONY: clean

clean:
	rm *.o
