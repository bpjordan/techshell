
CC=gcc
CFLAGS=-Wall
DEBUG=-g -Og -DDEBUG
PROD=-O3
LIB=
BIN=techshell
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, %.o, $(SRC))

all:$(BIN)

$(BIN):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIB)

%.o:%.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

prod:CFLAGS+=$(PROD)
prod:clean all

debug:CFLAGS+=$(DEBUG)
debug:all

clean:
	$(RM) $(OBJ) testfiles/*
