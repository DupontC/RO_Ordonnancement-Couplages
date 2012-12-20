CXX=gcc
CFLAGS=-Wall -ggdb
BIN=programme_name

SRC=$(wildcard src/*.c)
OBJ=$(SRC:src/%.c=build/%.o)
DEPS=$(SRC:src/%.c=build/%.d)

all: $(OBJ)
	$(CXX) -o $(BIN) $^

build/%.o: src/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

build/%.d: src/%.c
	$(CC) $(CFLAGS) -MM -MD -o $@ $<

clean:
	rm -f build/*.o
	rm -f build/*.d

mrproper: clean
	rm -f $(BIN)

.PHONY: clean mrproper

zip:
	tar -zcvf $(BIN).tar.gz $(SRC) $^
    