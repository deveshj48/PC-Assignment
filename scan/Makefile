INC="./inc"
FLAGS=-I$(INC)
OMPFLAG=-fopenmp
CC=gcc
P1=scan
P2=scan_omp
P3=scan_mpi


all: $(P1) $(P2) $(P3)

$(P1): $(P1).c
	$(CC) $(CFLAGS) $(OMPFLAG) $(P1).c -o $(P1) -lm
$(P2): $(P2).c
	$(CC) $(CFLAGS) $(OMPFLAG) $(P2).c -o $(P2) -lm
$(P3): $(P3).c
	$(CC) $(CFLAGS) $(OMPFLAG) $(P3).c -o $(P3) -lm


clean:
	rm $(P1) $(P2) $(P3) $(P4)
