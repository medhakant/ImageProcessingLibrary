CC = g++ -c
FILES = main.cpp CIL.cpp pthreadsConv.cpp cblasConv.cpp mklConv.cpp
OBJ = CIL.o pthreadsConv.o cblasConv.o mklConv.o
OMPFLAGS = -fopenmp
BLASFLAGS =  -I ~/BLAS/include/ -L ~/BLAS/lib -lopenblas -lpthread
MKLFLAGS =   -m64 -I ~/intel/mkl/include -L~/intel/mkl/lib/intel64 -lmkl_scalapack_lp64 -L~/intel/mkl/lib/intel64 -lmkl_intel_lp64 -L~/intel/mkl/lib/intel64 -lmkl_gnu_thread -L~/intel/mkl/lib/intel64 -lmkl_core -L~/intel/mkl/lib/intel64 -lmkl_blacs_intelmpi_lp64 -lgomp -lpthread -lm -ldl
CFLAGS = -I.


main: main.o $(OBJ) $(HEAD)
	g++ -o main main.o $(OBJ) $(CFLAGS) $(OMPFLAGS) $(BLASFLAGS) $(MKLFLAGS)

main.o: $(OBJ) $(HEAD) 
	$(CC) main.cpp $(CFLAGS)

pthreadsConv.o: $(HEAD) 
	$(CC) pthreadsConv.cpp $(OMPFLAGS) $(CFLAGS)

CIL.o: $(HEAD) 
	$(CC) CIL.cpp $(CFLAGS)

cblasConv.o: $(HEAD) 
	$(CC) cblasConv.cpp $(BLASFLAGS)

mklConv.o: $(HEAD) 
	$(CC) mklConv.cpp $(MKLFLAGS) $(CFLAGS)

clean:
	rm image *.o
