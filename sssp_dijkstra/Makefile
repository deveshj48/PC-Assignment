P1 = sssp
P2 = sssp_omp

CC = gcc
MPI = mpicc
CFLAGS = -g -Wall
OMPFLAG = -fopenmp

all: $(P1) $(P2) $(P3)

$(P1): $(P1).c
	$(CC) $(CFLAGS) $(OMPFLAG) $(P1).c -o $(P1)

$(P2): $(P2).c
	$(CC) $(CFLAGS) $(OMPFLAG) $(P2).c -o $(P2)

clean:
	rm -vf $(P1) $(P2)
