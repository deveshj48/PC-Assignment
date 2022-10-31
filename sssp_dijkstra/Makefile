P1 = sssp_omp
P2 = sssp
#Choose either the C compiler or the C++ compiler from the following 2 lines
CC = gcc
CFLAGS = -g -Wall
OMPFLAG = -fopenmp

all: $(P1) $(P2)

$(P1): $(P1).c
	$(CC) $(CFLAGS) $(OMPFLAG) $(P1).c -o $(P1)

$(P2): $(P2).c
	$(CC) $(CFLAGS) $(OMPFLAG) $(P2).c -o $(P2)

clean:
	rm -vf $(P1) $(P2)
