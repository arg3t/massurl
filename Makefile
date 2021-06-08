##
# massurl
#
# @file Makefile
# @version 0.1

VERSION = 0.1
CC = gcc
CFLAGS = -g -w
SRC = linkedlist.c urlparse.c tree.c massurl.c

all: massurl

massurl: $(SRC)
	${CC} $(SRC) -o massurl $(CFLAGS)


# end
