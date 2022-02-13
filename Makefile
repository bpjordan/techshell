
CC=gcc
CFLAGS=-Wall
DEBUG=-g -Og -DDEBUG
PROD=-O3
LIB=
BIN=techshell

all:$(BIN)

techshell: techshell.c
	$(CC) $(CFLAGS) $< -o $@ $(LIB)

prod:CFLAGS+=$(PROD)
prod:clean all

debug:CFLAGS+=$(DEBUG)
debug:all

clean:
	$(RM) $(BIN)
