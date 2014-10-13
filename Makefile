# Nom du compilateur
CC	= gcc

# Options du compilateur
CFLAGS 	= -Wall 
CFLAGS  += -Werror
CFLAGS 	+= -pedantic

CFLAGS += -D_XOPEN_SOURCE=500
CFLAGS += -g

all: palette
.PHONY: clean realclean


palette: palette.o
	$(CC) $(CFLAGS) -o palette palette.o

palette.o : palette.c palette.h
	$(CC) $(CFLAGS) -c palette.c 

clean:
	$(RM) *.o *~

realclean: clean
	$(RM) palette
