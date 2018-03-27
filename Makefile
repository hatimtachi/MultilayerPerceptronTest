CC=gcc
SRC=readFile.c NeuronConfiguration.c main.c
CFLAGS=-Wall -g
LDFLAGS = 
PROGRAMS = Pmc
platform=$(shell uname -s)
ifeq ($(platform),Darwin)
	OBJ=$(SRC:.c=.o) 
else
	OBJ=$(SRC:.c=.o) -lm
endif
all : $(PROGRAMS)
Pmc:    $(OBJ) NeuronStructure.h 
	$(CC)  -o $@ $(OBJ)
%.o:	%.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -rf $(PROGRAMS) *.o 
