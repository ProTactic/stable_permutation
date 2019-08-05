CC = gcc
CFLAGS = -c -Wall
OBJ = main.o spr.o utils/Link.o utils/LinkList.o

install: spr clean

all: spr

spr: $(OBJ)
	$(CC) main.o spr.o Link.o LinkList.o -o $@

linked_list: utils/Link.c utils/LinkList.c
	$(CC) $(CFLAGS) $?

clean:
	rm -rf *o

.c.o:
	$(CC) $(CFLAGS) $<

