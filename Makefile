CC=gcc
CFLAGS=-I.
INC = func.h
OBJECTS= main.o func.o
PROGRAM= Sorteo

$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) 

%.o: %.c $(INC)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm $(PROGRAM) $(OBJECTS)

