
CC=gcc
CFLAGS=-Wall
DEBUG=-g -Og -DDEBUG
PROD=-O3
LIB=
BIN=techshell
SRCD=src
OBJD=obj
SRC=$(wildcard $(SRCD)/*.c)
OBJ=$(patsubst $(SRCD)/%.c, $(OBJD)/%.o, $(SRC))

all:$(BIN)

$(BIN):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIB)

$(OBJD)/%.o:$(SRCD)/%.c $(SRCD)/%.h | $(OBJD)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJD):
	mkdir $@

prod:CFLAGS+=$(PROD)
prod:clean all

debug:CFLAGS+=$(DEBUG)
debug:all

clean:
	$(RM) $(OBJ) testfiles/*
