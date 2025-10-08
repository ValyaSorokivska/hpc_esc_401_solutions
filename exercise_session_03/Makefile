CC = cc
CFLAGS = -O3
LDFLAGS =

all: cpi

cpi: cpi.o gettime.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

cpi.o: cpi.c gettime.h
gettime.o: gettime.c gettime.h

clean:
	rm -f cpi *.o
.PHONY: all clean
