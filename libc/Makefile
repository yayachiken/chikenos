#
# Makefile for the ChikenOS libc
#

OBJ = src/string.o

libc.a: $(OBJ)
	ar -rcs $@ $+

src/%.o: src/%.c
	gcc -c -Wall -I./include/ -o $@ $<

clean:
	rm -f libc.a src/*.o

.PHONY: clean

