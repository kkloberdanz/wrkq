CC=cc
CFLAGS=-Werror -Wall -Wextra -std=c89 $(OPT) -fPIC -I./include
LDFLAGS=-L. -pthread -l:libwrkq.a
SRC=$(wildcard src/*.c)
INC=$(wildcard include/*.h)
OBJ=$(patsubst src/%.c,%.o,$(SRC))

.PHONY: release
release: libwrkq.so libwrkq.a
release: OPT:=-Os

.PHONY: debug
debug: libwrkq.so libwrkq.a
debug: OPT:=-O0 -ggdb3

.PHONY: sanitize
sanitize: libwrkq.so libwrkq.a
sanitize: OPT:=-O0 -ggdb3 \
	-fsanitize=address \
	-fsanitize=leak \
	-fsanitize=undefined
sanitize: test

test: OPT:=-O0 -ggdb3
test: libwrkq.so libwrkq.a
	$(CC) -o test tests/test.c $(CFLAGS) $(LDFLAGS)

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
	rm -f test
