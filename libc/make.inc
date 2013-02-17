#
# Makefile for the ChikenOS libc
#

LIBC_OBJ = $(LIBC_PATH)/src/string.o

libc.a: $(LIBC_OBJ)
	@ar -rcs $@ $+

$(LIBC_PATH)/src/%.o: $(LIBC_PATH)/src/%.c
	@$(CC) -m32 -c $(GLOBAL_CC_OPTS) -I$(LIBC_PATH)/include/ -o $@ $<

libc_clean:
	rm -f $(LIBC_PATH)/src/*.o
