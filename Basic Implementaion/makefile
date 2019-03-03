CC=g++
CFLAGS=-I.
DEPS = CIL.h
OBJ = CIL.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)