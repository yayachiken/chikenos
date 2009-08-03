#
# Makefile for the ChikenOS libc
#

LIBC_OBJ = $(LIBC_PATH)/src/string.o

libc.a: $(LIBC_OBJ)
	ar -rcs $@ $+

$(LIBC_PATH)/src/%.o: $(LIBC_PATH)/src/%.c
	gcc -m32 -c -Wall -I$(LIBC_PATH)/include/ -o $@ $<

libc_clean:
	rm -f $(LIBC_PATH)/libc.a $(LIBC_PATH)/src/*.o
