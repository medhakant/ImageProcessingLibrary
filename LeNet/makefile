CC=g++
CFLAGS=-I.
DEPS = CIL.h
OBJ = CIL.o net.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

leNet: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)