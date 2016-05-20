#
# Stampede - TACC 
#
# Intel Compilers are loaded by default; for other compilers please check the module list
#
CC = icpc
MPCC = mpicxx
OPENMP = -openmp
CFLAGS = -O3


TARGETS = sequentialDS sequentialFW openmpFW openmpDS

all:	$(TARGETS)

sequentialFW: sequentialFW.o common.o
	$(CC) -o $@ sequentialFW.o common.o
sequentialDS: sequentialDS.o common.o
	$(CC) -o $@ sequentialDS.o common.o
openmpFW: openmpFW.o common.o
	$(CC) -o $@ $(OPENMP) openmpFW.o common.o
openmpDS: openmpDS.o common.o
	$(CC) -o $@ $(OPENMP) openmpDS.o common.o

openmpFW.o: openmpFW.cpp common.h
	$(CC) -c $(OPENMP) $(CFLAGS) openmpFW.cpp
openmpDS.o: openmpDS.cpp common.h
	$(CC) -c $(OPENMP) $(CFLAGS) openmpDS.cpp
sequentialDS.o: sequentialDS.cpp common.h
	$(CC) -c $(CFLAGS) sequentialDS.cpp
sequentialFW.o: sequentialFW.cpp common.h
	$(CC) -c $(CFLAGS) sequentialFW.cpp
common.o: common.cpp common.h
	$(CC) -c $(CFLAGS) common.cpp

clean:
	rm -f *.o $(TARGETS) *.stdout *.txt
