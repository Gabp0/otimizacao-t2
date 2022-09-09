VPATH = src/

CC = gcc
CFLAGS = -lstdc++

objs = main.o cast.o actor.o 

all: elenco

elenco: $(objs)
	$(CC) $(objs) $(CFLAGS) -o elenco

main.o: main.cpp cast.h
cast.o: cast.cpp cast.h actor.h
actor.o: actor.cpp actor.h

clean:
	-rm -f $(objs) *~
purge: clean
	-rm -f elenco
