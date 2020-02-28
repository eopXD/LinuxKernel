CFLAGS = -Wall -g -Werror

OBJS = strnatcmp.o natsort.o

.PHONY: clean test

natsort: $(OBJS)
	$(CC) -o $@ $(OBJS)
test:
	$(CC) -o $@ test.c strnatcmp.c

clean:
	rm -rf natsort test $(OBJS)
