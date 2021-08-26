CC=cc
CFLAGS=-Werror -Wall -Wextra -std=c89 $(OPT) -fPIC -I./include
LDFLAGS=-lpthread
SRC=$(wildcard src/*.c)
INC=$(wildcard include/*.h)
OBJ=$(patsubst src/%.c,%.o,$(SRC))

.PHONY: release
release: libwrkq.so libwrkq.a
release: OPT:=-Os

.PHONY: debug
debug: libwrkq.so libwrkq.a
debug: OPT:=-O0 -ggdb3

libwrkq.so: $(OBJ)
	$(CC) -shared -o libwrkq.so $(CFLAGS) $(OBJ)

libwrkq.a: $(OBJ)
	ar rcs libwrkq.a $(OBJ)

%.o: src/%.c $(INC) $(SRC)
	$(CC) -c -o $@ $(CFLAGS) $<

.PHONY: clean
clean:
	rm -f *.o
	rm -f libwrkq.so
	rm -f libwrkq.a
	rm -f core
